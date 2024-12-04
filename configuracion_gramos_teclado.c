#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

#define ROWS 4
#define COLS 4

// Pines para las filas y columnas del teclado matricial
const uint8_t rowPins[ROWS] = {9, 8, 7, 6};
const uint8_t colPins[COLS] = {2, 5, 4, 3};

// Pines para los LEDs
const uint LED_VERDE = 14; // LED verde
const uint LED_ROJO = 15;  // LED rojo
int gramos = 0;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

void setup()
{
    // Configuración de las filas como salidas
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 1); // Activa la resistencia pull-up
    }

    // Configuración de las columnas como entradas
    for (int i = 0; i < COLS; i++)
    {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_IN);
        gpio_pull_up(colPins[i]); // Activa la resistencia pull-up
    }

    // Configuración de los LEDs como salidas
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0); // LED apagado inicialmente

    gpio_init(LED_ROJO);
    gpio_set_dir(LED_ROJO, GPIO_OUT);
    gpio_put(LED_ROJO, 0); // LED apagado inicialmente
}

char scanKeypad()
{
    for (int row = 0; row < ROWS; row++)
    {
        gpio_put(rowPins[row], 0); // Activa la fila actual (LOW)
        for (int col = 0; col < COLS; col++)
        {
            if (gpio_get(colPins[col]) == 0) // Detecta si se presionó una tecla
            {
                sleep_ms(50); // Debounce
                if (gpio_get(colPins[col]) == 0) // Verifica si sigue presionada
                {
                    while (gpio_get(colPins[col]) == 0)
                        ; // Espera a que se suelte
                    gpio_put(rowPins[row], 1); // Restaura la fila
                    return keys[row][col];     // Retorna la tecla presionada
                }
            }
        }
        gpio_put(rowPins[row], 1); // Restaura la fila
    }
    return '\0'; // Sin tecla presionada
}

void configurar_porcion(char *porcion)
{
    int i = 0;
    bool porcion_completada = false;

    printf("Configuración de porción en gramos:\n");

    while (true)
    {
        char key = scanKeypad();
        if (key != '\0' && key >= '0' && key <= '9') // Solo números
        {
            porcion[i++] = key;
            printf("Porción: %s\n", porcion);

            if (i == 4) // Máximo 4 dígitos (9999)
            {
                porcion[4] = '\0'; // Aseguramos el fin de cadena
                gramos = atoi(porcion);

                if (gramos >= 0 && gramos <= 9999)
                {
                    porcion_completada = true;
                    gpio_put(LED_VERDE, 1); // LED verde encendido
                    gpio_put(LED_ROJO, 0);  // LED rojo apagado
                    sleep_ms(1000);
                    gpio_put(LED_VERDE, 0);
                    gpio_put(LED_ROJO, 0); 
                }
                else
                {
                    gpio_put(LED_VERDE, 0); // LED verde apagado
                    gpio_put(LED_ROJO, 1); // LED rojo encendido
                    printf("Porción inválida, reiniciando...\n");
                }

                i = 0; // Reiniciar para capturar otra entrada
                memset(porcion, 0, sizeof(char) * 5);
            }
        }

        if (porcion_completada)
        {
            break;
        }
    }
}

int main()
{
    stdio_init_all();
    setup();

    while (true)
    {
        char keyinicial = scanKeypad();
        if (keyinicial != '\0')
        {
            printf("Tecla presionada: %c\n", keyinicial);
            if (keyinicial == 'A') // Inicia configuración
            {
                char porcion[5] = {0}; // Buffer para la porción
                configurar_porcion(porcion);
                printf("Porción válida: %d gramos\n", gramos);
            }
        }
    }

    return 0;
}
