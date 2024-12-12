#ifndef MOSTRAR_EN_DISPLAYS_H
#define MOSTRAR_EN_DISPLAYS_H

#include <stdint.h>
#include "pico/stdlib.h"

// Pines de los segmentos y transistores
extern uint8_t display_pins[]; /**< Array de pines correspondientes a los segmentos A-G de los displays de 7 segmentos. */
extern uint8_t transistor_pins[]; /**< Array de pines correspondientes a los transistores de control de los displays. */

// Mapeo de los números 0-9 en segmentos de 7 segmentos
extern uint8_t segment_map[]; /**< Mapeo de los dígitos 0-9 a su representación en segmentos de 7 segmentos. */
extern uint8_t letter_map[]; /**< Mapeo de las letras H, O, L, A a su representación en segmentos de 7 segmentos. */

/**
 * @brief Inicializa los pines de los segmentos y los transistores.
 * 
 * Configura los pines correspondientes a los segmentos de los displays de 7 segmentos
 * y los pines de control de los transistores para el multiplexado de los displays.
 */
void init_pins2();

/**
 * @brief Muestra un dígito en un display específico.
 * 
 * Esta función configura los pines de los segmentos para mostrar el dígito especificado
 * en el display correspondiente, y activa el transistor asociado al display.
 *
 * @param digit El dígito a mostrar (0-9).
 * @param display El índice del display (0-3).
 */
void show_digit(uint8_t digit, uint8_t display);

/**
 * @brief Muestra un número de 4 dígitos en los displays.
 * 
 * La función descompone el número en 4 dígitos y los muestra en los displays de 7 segmentos,
 * multiplexando los displays rápidamente para hacer que todos sean visibles.
 *
 * @param number El número de 4 dígitos a mostrar (0-9999).
 */
void show_number(int number);

/**
 * @brief Muestra una letra en un display específico.
 * 
 * Esta función muestra una letra (H, O, L, A) en un display de 7 segmentos,
 * activando los segmentos correspondientes de acuerdo con el mapeo de la letra.
 *
 * @param letter La letra a mostrar (debe ser una de las letras mapeadas: H, O, L, A).
 * @param display_index El índice del display (0-3) donde se mostrará la letra.
 */
void show_letter(uint8_t letter, uint8_t display_index);

#endif // MOSTRAR_EN_DISPLAYS_H
