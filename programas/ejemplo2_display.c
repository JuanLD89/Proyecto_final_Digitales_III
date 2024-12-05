#include <stdio.h>
#include "pico/stdlib.h"

// Pines de los segmentos y transistores
uint8_t display_pins[] = {27, 28, 13, 12, 11, 26, 10}; // A, B, C, D, E, F, G
uint8_t transistor_pins[] = {17, 16, 18, 19};          // Transistores para cada display

// Mapeo de los números 0-9 en segmentos de 7 segmentos (sin el punto decimal como bit 7)
uint8_t segment_map[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

#define ROWS 4
#define COLS 4

// Pines para las filas y columnas del teclado matricial
const uint8_t rowPins[ROWS] = {9, 8, 7, 6};
const uint8_t colPins[COLS] = {2, 5, 4, 3};

// Pines para los LEDs
const uint LED_VERDE = 14; // LED verde
const uint LED_ROJO = 15;  // LED rojo
int horas0 = 0;
int minutos0 = 0;

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
                sleep_ms(50);                    // Debounce
                if (gpio_get(colPins[col]) == 0) // Verifica si sigue presionada
                {
                    while (gpio_get(colPins[col]) == 0)
                        ;                      // Espera a que se suelte
                    gpio_put(rowPins[row], 1); // Restaura la fila
                    return keys[row][col];     // Retorna la tecla presionada
                }
            }
        }
        gpio_put(rowPins[row], 1); // Restaura la fila
    }
    return '\0'; // Sin tecla presionada
}

// Inicialización de los pines de salida
void init_pins()
{
    for (int i = 0; i < 8; i++)
    {
        gpio_init(display_pins[i]);
        gpio_set_dir(display_pins[i], GPIO_OUT);
    }
    for (int i = 0; i < 4; i++)
    {
        gpio_init(transistor_pins[i]);
        gpio_set_dir(transistor_pins[i], GPIO_OUT);
    }
}

// Mostrar un dígito en un display específico
void show_digit(uint8_t digit, uint8_t display)
{
    // Apagar todos los transistores para evitar superposición
    for (int i = 0; i < 4; i++)
    {
        gpio_put(transistor_pins[i], 0);
    }

    // Configurar los pines de los segmentos para mostrar el dígito
    uint8_t segments = segment_map[digit];
    for (int i = 0; i < 8; i++)
    {
        gpio_put(display_pins[i], (segments >> i) & 1);
    }

    // Encender el transistor correspondiente al display
    gpio_put(transistor_pins[display], 1);

    // Esperar para que el dígito sea visible antes de apagarlo
    sleep_ms(2);

    // Apagar el transistor del display
    gpio_put(transistor_pins[display], 0);
}

// Mostrar un número en los 4 displays
void show_number(int number)
{
    uint8_t digits[4] = {
        (number / 1000) % 10, // Milésimas
        (number / 100) % 10,  // Centésimas
        (number / 10) % 10,   // Decenas
        number % 10           // Unidades
    };

    // Multiplexar los 4 displays rápidamente
    for (int i = 0; i < 4; i++)
    {
        show_digit(digits[i], i);
    }
}

void configurar_hora(char *horas, char *minutos)
{
    int i = 0, j = 0;
    bool horacompletada = false;
    bool minutoscompletados = false;

    printf("Configuración de la hora:\n");

    while (true)
    {
        char key = scanKeypad();
        if (key != '\0' && key >= '0' && key <= '9') // Solo números
        {
            if (!horacompletada)
            {
                horas[i++] = key;
                printf("Horas: %s\n", horas);
                horas0 = atoi(horas);
                if (i == 2)
                {
                    horas[2] = '\0';
                    int hora = atoi(horas);
                    if (hora >= 0 && hora <= 23)
                    {
                        horacompletada = true;
                        gpio_put(LED_VERDE, 1); // LED verde encendido
                        gpio_put(LED_ROJO, 0);  // LED rojo apagado
                        printf("Hora válida: %s\n", horas);
                    }
                    else
                    {
                        gpio_put(LED_VERDE, 0); // LED verde apagado
                        gpio_put(LED_ROJO, 1);  // LED rojo encendido
                        printf("Hora inválida, reiniciando...\n");
                        horas0 = 0;
                        memset(horas, 0, sizeof(horas));
                        i = 0;
                    }
                }
            }
            else if (!minutoscompletados)
            {
                minutos[j++] = key;
                printf("Minutos: %s\n", minutos);
                minutos0 = atoi(minutos);
                if (j == 2)
                {
                    minutos[2] = '\0';
                    int minuto = atoi(minutos);
                    if (minuto >= 0 && minuto <= 59)
                    {
                        minutoscompletados = true;
                        gpio_put(LED_VERDE, 1); // LED verde encendido
                        gpio_put(LED_ROJO, 0);  // LED rojo apagado
                        printf("Minutos válidos: %s\n", minutos);
                    }
                    else
                    {
                        gpio_put(LED_VERDE, 0); // LED verde apagado
                        gpio_put(LED_ROJO, 1);  // LED rojo encendido
                        printf("Minutos inválidos, reiniciando...\n");
                        minutos0 = 0;
                        memset(minutos, 0, sizeof(minutos));
                        j = 0;
                    }
                }
            }
        }
        show_number(horas0 * 100 + minutos0);
        if ((horacompletada && minutoscompletados) && key == '#')
        {
            gpio_put(LED_VERDE, 1); // LED verde encendido
            gpio_put(LED_ROJO, 0);  // LED rojo apagado
            sleep_ms(1000);
            gpio_put(LED_VERDE, 0);
            gpio_put(LED_ROJO, 0);
            break;
        }
    }
}

int main()
{
    stdio_init_all();
    init_pins();
    setup();

    while (true)
    {
        char keyinicial = scanKeypad();
        if (keyinicial != '\0')
        {
            printf("Tecla presionada: %c\n", keyinicial);
            if (keyinicial == 'A') // Inicia configuración
            {
                char horas[3] = {0};   // Buffer para horas
                char minutos[3] = {0}; // Buffer para minutos
                configurar_hora(horas, minutos);
                int horas_int = atoi(horas);
                int minutos_int = atoi(minutos);
                printf("Hora configurada: %d:%d\n", horas_int, minutos_int);
            }
        }
    }

    return 0;
}
