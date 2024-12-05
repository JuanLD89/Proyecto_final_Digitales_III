#ifndef CONFIGURACION_GRAMOS_TECLADO_H
#define CONFIGURACION_GRAMOS_TECLADO_H

#include <stdint.h>
#include "configuracion_porcion_teclado.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include "mostrar_en_displays.h"


// Definición de filas, columnas y LEDs
#define ROWS 4
#define COLS 4

//extern const uint8_t rowPins[ROWS];
//extern const uint8_t colPins[COLS];
//extern char keys[ROWS][COLS];

// Variables globales
extern int gramos;

// Prototipos de funciones
//void setup();
//char scanKeypad();
void configurar_porcion(char *porcion);

#endif // CONFIGURACION_GRAMOS_TECLADO_H
