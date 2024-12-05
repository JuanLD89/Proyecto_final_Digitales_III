#ifndef CONFIGURACION_TIEMPO_TECLADO_H
#define CONFIGURACION_TIEMPO_TECLADO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include <string.h>

// Definiciones de pines y constantes
#define ROWS 4
#define COLS 4

extern const uint8_t rowPins[ROWS];
extern const uint8_t colPins[COLS];
extern const uint LED_VERDE;
extern const uint LED_ROJO;
extern volatile bool key_pressed;

extern char keys[ROWS][COLS];

// Declaraciones de funciones
void setup(void);
char scanKeypad(void);
void gpio_callback(uint gpio, uint32_t events);
void configurar_hora(char *horas, char *minutos);

#endif // CONFIGURACION_TIEMPO_TECLADO_H
