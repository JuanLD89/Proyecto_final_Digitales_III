#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ROWS 4
#define COLS 4
#define MAX_ID_LENGTH 6
#define MAX_CLAVE_LENGTH 4

const uint LedRojo = 14;
const uint LedVerde = 15;

int numeroIntentos = 0;

const uint8_t rowPins[ROWS] = {9, 8, 7, 6}; 
const uint8_t colPins[COLS] = {2, 5, 4, 3}; 

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

typedef struct
{
    char id[MAX_ID_LENGTH + 1];     ///< ID del usuario (hasta 6 dígitos).
    char clave[MAX_CLAVE_LENGTH + 1]; ///< Clave del usuario (hasta 4 dígitos).
} Usuario;

Usuario baseDeDatos = {"123456", "1111"};

void setup()
{
    // Inicializa los pines de las filas como salida
    for (int i = 0; i < ROWS; i++)
    {
        gpio_init(rowPins[i]);
        gpio_set_dir(rowPins[i], GPIO_OUT);
        gpio_put(rowPins[i], 1); // Activa la resistencia pull-up
    }

    // Inicializa los pines de las columnas como entrada
    for (int i = 0; i < COLS; i++)
    {
        gpio_init(colPins[i]);
        gpio_set_dir(colPins[i], GPIO_IN);
        gpio_pull_up(colPins[i]); // Activa la resistencia pull-up
    }
}

char scanKeypad()
{
    for (int row = 0; row < ROWS; row++)
    {
        // Activa la fila actual
        gpio_put(rowPins[row], 0); // Baja a bajo
        for (int col = 0; col < COLS; col++)
        {
            // Lee la columna
            if (gpio_get(colPins[col]) == 0)
            {
                // Espera a que se suelte la tecla
                sleep_ms(50);
                if (gpio_get(colPins[col]) == 0)
                { // Verifica si sigue presionado
                    // Espera a que se suelte la tecla
                    while (gpio_get(colPins[col]) == 0)
                        ;
                    gpio_put(rowPins[row], 1); // Restaura la fila
                    return keys[row][col];     // Retorna la tecla presionada
                }
            }
        }
        gpio_put(rowPins[row], 1); // Restaura la fila
    }
    return '\0'; // Sin tecla presionada
}

int verificarUsuario(const char *id, const char *clave)
{
    if (strcmp(baseDeDatos.id, id) == 0 && strcmp(baseDeDatos.clave, clave) == 0)
    {
        return 1; // Usuario verificado
    }
    return 0; // Verificación fallida
}

void encenderLedVerde()
{
    printf("Acceso concedido.\n");
    gpio_put(LedVerde, 1);
    sleep_ms(10000);    //10 segundos prendido (tiempo para abrir la compuerta, si no se vuelve a bloquear)
    gpio_put(LedVerde, 0);
    sleep_ms(500);
}

void encenderLedRojo()
{
    printf("Acceso denegado.\n");
    gpio_put(LedRojo, 1);
    sleep_ms(2000); //2 segundos prendido (tiempo para indicar clave erronea)
    gpio_put(LedRojo, 0);
    sleep_ms(500);
}

int manejarAutenticacion(char *tempId, char *tempClave)
{

    printf("Ingrese su ID y clave:\n");
    int idComplete = 0;
    int claveComplete = 0;
    absolute_time_t last_change_time = get_absolute_time();
    const uint32_t interval = 1000 * 1000; // 1 segundo en microsegundos
    while (1)
    {

        char key = scanKeypad();
        if (key != '\0')
        {
            if (!idComplete && strlen(tempId) < MAX_ID_LENGTH)
            {
                strncat(tempId, &key, 1); // Añade un solo carácter al ID
                if (strlen(tempId) == MAX_ID_LENGTH)
                {
                    idComplete = 1; // ID completo
                }
            }
            else if (idComplete && !claveComplete && strlen(tempClave) < MAX_CLAVE_LENGTH)
            {
                strncat(tempClave, &key, 1); // Añade un solo carácter a la clave
                if (strlen(tempClave) == MAX_CLAVE_LENGTH)
                {
                    claveComplete = 1; // Clave completa
                }
            }
        }
        if (idComplete)
        {
            if (absolute_time_diff_us(last_change_time, get_absolute_time()) >= interval)
            {
                // Actualiza el tiempo del último cambio
                last_change_time = get_absolute_time();
            }
            
        }

        if (idComplete && claveComplete)
        {
            break; // Salir si se completaron ID y clave
        }
    }

    // Mostrar ID y clave ingresados
    printf("ID ingresado: %s\n", tempId);
    printf("Clave ingresada: %s\n", tempClave);

    if (verificarUsuario(tempId, tempClave))
    {
        encenderLedVerde();
        return 1; // Autenticación exitosa
    }
    else
    {
        encenderLedRojo();
        return 0; // Falló la autenticación
    }

}

int main()
{
    stdio_init_all();
    setup();

    // Configura el pin como salida
    gpio_init(LedRojo);
    gpio_set_dir(LedRojo, GPIO_OUT);
    gpio_init(LedVerde);
    gpio_set_dir(LedVerde, GPIO_OUT);

    while (true)
    {
        char tempId[MAX_ID_LENGTH + 1] = {0};
        char tempClave[MAX_CLAVE_LENGTH + 1] = {0};
        char keyinicial = scanKeypad();

        if (keyinicial != '\0')
        {
            printf("Tecla presionada: %c\n", keyinicial);
            if (keyinicial == '*')
            {
                if (manejarAutenticacion(tempId, tempClave))
                {
                    printf("Usuario autenticado.\n");
                }
                else
                {
                    printf("Fallo en la autenticación.\n");
                }
            }
        }
    }

    return 0;
}