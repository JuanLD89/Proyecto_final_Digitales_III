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
const uint LedAmarillo = 16;

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

typedef struct
{
    char idIntentos[MAX_ID_LENGTH + 1]; ///< ID del usuario.
    int Intentos;                       ///< Número de intentos fallidos.
} UsuarioIntentos;

UsuarioIntentos baseDeDatosIntentos = {"123456", 0};

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
    // si falla sumar a numero de intentos fallidos

    int NIntentos = 0;
    int NIntentosNuvo = 1;

    if (strcmp(baseDeDatosIntentos.idIntentos, id) == 0)
    {
        NIntentos = baseDeDatosIntentos.Intentos; // Retorna el número de intentos
    }
    
    NIntentosNuvo = NIntentos + 1;
    if (strcmp(baseDeDatosIntentos.idIntentos, id) == 0)
    {
        baseDeDatosIntentos.Intentos = NIntentosNuvo;
        printf("Se sumo un error.\n");
        printf("intentos: %d\n", NIntentosNuvo);
    }
    return 0; // Verificación fallida
}