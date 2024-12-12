/**
 * @file configuracion_tiempo_teclado.c
 * @brief Configuración de la hora con teclado matricial.
 *
 * Este archivo contiene funciones para configurar la hora (horas y minutos)
 * con el teclado matricial.
 */

#include "configuracion_tiempo_teclado.h"

/// Bandera para indicar si se presionó una tecla.
volatile bool key_pressed = false;

/// Pines correspondientes a las filas del teclado matricial.
const uint8_t rowPins[ROWS] = {9, 8, 7, 6};

/// Pines correspondientes a las columnas del teclado matricial.
const uint8_t colPins[COLS] = {2, 5, 4, 3};

/// Variable que almacena las horas configuradas.
int horas0 = 0;

/// Variable que almacena los minutos configurados.
int minutos0 = 0;

/// Matriz que define las teclas del teclado matricial.
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

/**
 * @brief Callback de interrupción para manejar la detección de teclas.
 *
 * Esta función se activa cuando ocurre un cambio de estado en los pines de las columnas.
 * 
 * @param gpio Número del pin que generó la interrupción.
 * @param events Evento que generó la interrupción.
 */
void gpio_callback(uint gpio, uint32_t events)
{
    key_pressed = true; // Activar la bandera
}

/**
 * @brief Configura los pines del teclado matricial y habilita interrupciones.
 *
 * - Configura las filas como salidas.
 * - Configura las columnas como entradas con resistencias pull-up activadas.
 * - Habilita interrupciones en los pines de las columnas.
 */
void setup()
{
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 1); // Inicializa las filas en estado HIGH
    }

    for (int i = 0; i < COLS; i++)
    {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_IN);
        gpio_pull_up(colPins[i]); // Activa resistencias pull-up

        // Configura interrupciones en bordes ascendente y descendente
        gpio_set_irq_enabled_with_callback(colPins[i], GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
        gpio_set_irq_enabled_with_callback(colPins[i], GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    }
}

/**
 * @brief Escanea el teclado matricial para detectar teclas presionadas.
 *
 * - Activa una fila a la vez (LOW).
 * - Comprueba las columnas para detectar si una tecla está presionada.
 * - Utiliza un retardo para evitar rebotes.
 *
 * @return El carácter de la tecla presionada, o '\0' si no hay ninguna tecla presionada.
 */
char scanKeypad()
{
    for (int row = 0; row < ROWS; row++)
    {
        gpio_put(rowPins[row], 0); // Activa la fila actual (LOW)
        for (int col = 0; col < COLS; col++)
        {
            if (gpio_get(colPins[col]) == 0) // Detecta si se presionó una tecla
            {
                sleep_ms(50); // Retardo para evitar rebotes
                if (gpio_get(colPins[col]) == 0) // Verifica si sigue presionada
                {
                    while (gpio_get(colPins[col]) == 0)
                        ; // Espera a que se suelte la tecla
                    gpio_put(rowPins[row], 1); // Restaura la fila
                    return keys[row][col];     // Retorna la tecla presionada
                }
            }
        }
        gpio_put(rowPins[row], 1); // Restaura la fila
    }
    return '\0'; // Sin tecla presionada
}

/**
 * @brief Configura la hora mediante el teclado matricial.
 *
 * Permite ingresar las horas y minutos en formato de 24 horas. Valida que las entradas
 * sean correctas y las muestra en un display durante el proceso.
 *
 * - Las horas deben estar en el rango [0, 23].
 * - Los minutos deben estar en el rango [0, 59].
 *
 * @param[in,out] horas Arreglo de caracteres para almacenar las horas ingresadas.
 * @param[in,out] minutos Arreglo de caracteres para almacenar los minutos ingresados.
 */
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
        
        show_number(horas0 * 100 + minutos0); // Muestra las horas y minutos combinados
        if ((horacompletada && minutoscompletados) && key == '#')
        {
            break;
        }
    }
}
