#ifndef MOSTRAR_EN_DISPLAYS_H
#define MOSTRAR_EN_DISPLAYS_H

#include <stdint.h>
#include "pico/stdlib.h"

// Pines de los segmentos y transistores
extern uint8_t display_pins[];
extern uint8_t transistor_pins[];

// Mapeo de los números 0-9 en segmentos de 7 segmentos
extern uint8_t segment_map[];
extern uint8_t letter_map[];

// Inicialización de los pines de salida
void init_pins2();

// Mostrar un dígito en un display específico
void show_digit(uint8_t digit, uint8_t display);

// Mostrar un número en los 4 displays
void show_number(int number);

// Mostrar una letra en un display específico
void show_letter(uint8_t letter, uint8_t display_index);

#endif // MOSTRAR_EN_DISPLAYS_H

