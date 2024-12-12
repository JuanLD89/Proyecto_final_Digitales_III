/**
 * @file sensor.h
 * @brief Declaraciones y configuraciones para el uso de un sensor.
 */

#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include "pico/stdlib.h"

/** 
 * @def ECHO_PIN 
 * @brief Pin GPIO conectado al pin ECHO del sensor. 
 */
#define ECHO_PIN 27

/** 
 * @def TRIGGER_PIN 
 * @brief Pin GPIO conectado al pin TRIGGER del sensor. 
 */
#define TRIGGER_PIN 28

/**
 * @brief Inicializa los pines del sensor.
 *
 * Configura el pin TRIGGER como salida y el pin ECHO como entrada.
 */
void init_pins();

/**
 * @brief Mide la duración de un pulso en alto en un pin GPIO.
 *
 * Esta función mide el tiempo que el pin especificado permanece en estado alto.
 *
 * @param pin Pin GPIO en el que se mide el pulso.
 * @return Duración del pulso en microsegundos.
 */
uint32_t measure_pulse_high(uint pin);

/**
 * @brief Mide la distancia utilizando un sensor.
 *
 * Genera un pulso de disparo (trigger) y mide la duración del pulso en alto 
 * del pin ECHO. Calcula la distancia en función del tiempo medido.
 *
 * @return Distancia medida en centímetros.
 */
float medir_distancia();

#endif // SENSOR_H
