#include "configuracion_tiempo_teclado.h"

volatile bool key_pressed = false; // Bandera para indicar que se presionó una tecla

// Pines para las filas y columnas del teclado matricial
const uint8_t rowPins[ROWS] = {9, 8, 7, 6};
const uint8_t colPins[COLS] = {2, 5, 4, 3};

int horas0 = 0;
int minutos0 = 0;

// Matriz de teclas
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Callback para interrupción de las columnas
void gpio_callback(uint gpio, uint32_t events)
{
    key_pressed = true; // Activar la bandera
}

// Configuración inicial de pines y interrupciones
void setup()
{
    // Configuración de las filas como salidas
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 1);
    }

    // Configuración de las columnas como entradas
    for (int i = 0; i < COLS; i++)
    {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_IN);
        gpio_pull_up(colPins[i]); // Activar resistencia pull-up

        // Configurar interrupción
        gpio_set_irq_enabled_with_callback(colPins[i], GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
        gpio_set_irq_enabled_with_callback(colPins[i], GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    }
}

// Escanear teclado matricial
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

// Configurar hora usando el teclado
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
                        printf("Hora válida: %s\n", horas);
                    }
                    else
                    {
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
                        printf("Minutos válidos: %s\n", minutos);
                    }
                    else
                    {
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
            break;
        }
    }
}
