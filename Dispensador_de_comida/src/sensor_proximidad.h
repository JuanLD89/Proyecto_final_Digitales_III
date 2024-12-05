#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include "pico/stdlib.h"

// Definición de pines
#define ECHO_PIN 26
#define TRIGGER_PIN 27

// Declaración de funciones
void init_pins();
uint32_t measure_pulse_high(uint pin);
float medir_distancia();

#endif // SENSOR_H