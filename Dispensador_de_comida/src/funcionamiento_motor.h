#ifndef FUNCIONAMIENTO_MOTOR_H
#define FUNCIONAMIENTO_MOTOR_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definición de pines
#define SERVO_PIN 18 // Cambia al pin GPIO que estés usandoç
#define MOTOBOMBA_PIN 19 // Cambia al pin GPIO que estés usando


// Prototipos de funciones
void init_servo(uint *slice_num, uint *channel);
void set_servo_speed(uint slice_num, uint channel, float speed);

#endif // FUNCIONAMIENTO_MOTOR_H
