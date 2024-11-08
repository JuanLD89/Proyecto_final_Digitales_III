#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

/** Número de filas del teclado matricial. */
#define ROWS 4

/** Número de columnas del teclado matricial. */
#define COLS 4

/** Longitud máxima permitida para la clave del usuario (4 caracteres). */
#define MAX_CLAVE_LENGTH 4

/** Pin asignado al LED rojo, utilizado para indicar acceso denegado. */
const uint LedRojo = 14;

/** Pin asignado al LED verde, utilizado para indicar acceso concedido. */
const uint LedVerde = 15;

/** Pin asignado al LED amarillo, utilizado para indicar estado de espera. */
const uint LedAmarillo = 16;

/** Contador global de intentos fallidos. */
int numeroIntentos = 0;

/** 
 * Pines de las filas del teclado matricial.
 * Cada valor en el array `rowPins` corresponde a un pin GPIO que controla una fila del teclado.
 */
const uint8_t rowPins[ROWS] = {9, 8, 7, 6}; 

/** 
 * Pines de las columnas del teclado matricial.
 * Cada valor en el array `colPins` corresponde a un pin GPIO que controla una columna del teclado.
 */
const uint8_t colPins[COLS] = {2, 5, 4, 3}; 


/**
 * Mapa de las teclas del teclado matricial.
 * La matriz `keys` representa el conjunto de teclas de un teclado matricial
 * de 4 filas y 4 columnas. Cada posición corresponde a una tecla específica. 
 */
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

typedef struct
{
    char clave[MAX_CLAVE_LENGTH + 1]; ///< Clave del usuario (hasta 4 dígitos).
} claves;

claves baseDeDatos = {"1111"};