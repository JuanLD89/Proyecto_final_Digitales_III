#ifndef FUNCIONAMIENTO_MOTOR_H
#define FUNCIONAMIENTO_MOTOR_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

/**
 * @file funcionamiento_motor.h
 * @brief Cabecera para el control del servo motor y la motobomba.
 *
 * Este archivo define los pines y funciones para inicializar y 
 * controlar un servo motor mediante PWM, así como una motobomba controlada por GPIO.
 */

// Definición de pines
#define SERVO_PIN 22 ///< Pin GPIO utilizado para el control del servo motor.
#define MOTOBOMBA_PIN 26 ///< Pin GPIO utilizado para controlar la motobomba.

// Prototipos de funciones

/**
 * @brief Inicializa el servo motor y la motobomba.
 *
 * Configura el pin del servo motor para operar con PWM y el pin de la motobomba como salida digital.
 *
 * @param slice_num Puntero donde se almacenará el número de slice del PWM.
 * @param channel Puntero donde se almacenará el canal del PWM.
 */
void init_servo(uint *slice_num, uint *channel);

/**
 * @brief Configura la velocidad del servo motor.
 *
 * Ajusta el ancho de pulso del PWM para controlar la velocidad y dirección del servo motor.
 *
 * @param slice_num Número del slice asociado al pin del servo motor.
 * @param channel Canal del PWM asociado al pin del servo motor.
 * @param speed Velocidad deseada del servo motor, en un rango de -1.0 a 1.0:
 *              - -1.0: Velocidad máxima antihoraria.
 *              -  0.0: Posición neutral (detenido).
 *              -  1.0: Velocidad máxima horaria.
 */
void set_servo_speed(uint slice_num, uint channel, float speed);

#endif // FUNCIONAMIENTO_MOTOR_H
