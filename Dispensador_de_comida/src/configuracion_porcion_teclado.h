/**
 * @file configuracion_gramos_teclado.h
 * @brief Encabezado para la configuración de porciones en gramos usando un teclado matricial.
 *
 * Este archivo contiene las definiciones, macros y  funciones necesarias
 * para implementar la configuración de porciones en gramos mediante un teclado matricial.
 */

#ifndef CONFIGURACION_GRAMOS_TECLADO_H
#define CONFIGURACION_GRAMOS_TECLADO_H

// Dependencias estándar y específicas
#include <stdint.h> 
#include "configuracion_porcion_teclado.h" ///< Funciones y variables relacionadas con la configuración de porciones.
#include "pico/stdlib.h" ///< Funciones estándar de la Raspberry Pi Pico.
#include <stdio.h> 
#include <string.h> 
#include "mostrar_en_displays.h" ///< Funciones para mostrar valores en los displays.

/**
 * @brief Número de filas y columnas del teclado matricial.
 */
#define ROWS 4 ///< Número de filas del teclado matricial.
#define COLS 4 ///< Número de columnas del teclado matricial.

// Variables globales

/**
 * @brief Variable global que almacena la cantidad de gramos configurada.
 */
extern int gramos;

// Prototipos de funciones

/**
 * @brief Configura la cantidad de gramos mediante un teclado matricial.
 *
 * Mira la entrada y determina si esta en el rango permitido
 * La cantidad se muestra en un display durante la configuración.
 *
 * @param[in,out] porcion Arreglo de caracteres para almacenar temporalmente la entrada del teclado.
 *                        Debe ser un arreglo de al menos 5 posiciones.
 */
void configurar_porcion(char *porcion);

#endif // CONFIGURACION_GRAMOS_TECLADO_H

