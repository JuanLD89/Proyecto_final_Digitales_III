#ifndef CONFIGURACION_TIEMPO_TECLADO_H
#define CONFIGURACION_TIEMPO_TECLADO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include <string.h>
#include "mostrar_en_displays.h"

// Definiciones de pines y constantes
#define ROWS 4  // Número de filas del teclado matricial
#define COLS 4  // Número de columnas del teclado matricial

// Pines y variables globales externas
extern const uint8_t rowPins[ROWS]; // Pines de las filas
extern const uint8_t colPins[COLS]; // Pines de las columnas
extern volatile bool key_pressed;  // Bandera para detección de teclas

// Matriz de teclas
extern char keys[ROWS][COLS]; 

// Declaraciones de funciones

/**
 * @brief Configura los pines del teclado matricial e inicializa las interrupciones.
 */
void setup(void);

/**
 * @brief Escanea el teclado matricial y detecta la tecla presionada.
 * @return Carácter de la tecla presionada o '\0' si no se presionó ninguna tecla.
 */
char scanKeypad(void);

/**
 * @brief Callback de interrupción para detectar cambios en las columnas.
 * @param gpio Número del pin que activó la interrupción.
 * @param events Eventos detectados.
 */
void gpio_callback(uint gpio, uint32_t events);

/**
 * @brief Configura la hora utilizando el teclado matricial.
 * @param horas Puntero a un arreglo donde se almacenarán las horas.
 * @param minutos Puntero a un arreglo donde se almacenarán los minutos.
 */
void configurar_hora(char *horas, char *minutos);

#endif // CONFIGURACION_TIEMPO_TECLADO_H
