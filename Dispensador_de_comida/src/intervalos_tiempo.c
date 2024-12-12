#include "intervalos_tiempo.h"
#include <stdio.h>

/**
 * @file intervalos_tiempo.c
 * @brief Implementación de funciones para manejar intervalos de tiempo y alarmas en el RTC.
 *
 * Aqui se pueden configurar intervalos de tiempo y gestionar alarmas
 * utilizando el RTC (Real-Time Clock) de la Raspberry Pi Pico.
 */

// Variables configurables para el intervalo
int alarm_interval_hours = 0;    ///< Horas del intervalo de alarma.
int alarm_interval_minutes = 0; ///< Minutos del intervalo de alarma.
int alarm_interval_seconds = 0; ///< Segundos del intervalo de alarma.

volatile bool alarm_triggered = false; ///< Bandera que indica si la alarma se ha activado.

/**
 * @brief Configura una alarma en el RTC después de un intervalo específico.
 *
 * Suma un intervalo definido (horas, minutos y segundos) al tiempo actual
 * y configura la alarma en el tiempo resultante.
 *
 * @param hours Número de horas que se sumarán al tiempo actual.
 * @param minutes Número de minutos que se sumarán al tiempo actual.
 * @param seconds Número de segundos que se sumarán al tiempo actual.
 */
void rtc_set_alarm_in_interval(int hours, int minutes, int seconds) {
    datetime_t current_time;
    rtc_get_datetime(&current_time);

    printf("Inicial: %02d:%02d:%02d\n", current_time.hour, current_time.min, current_time.sec);

    // Sumar el intervalo al tiempo actual
    current_time.sec += seconds;
    if (current_time.sec >= 60) {
        current_time.sec -= 60;
        current_time.min++;
    }

    current_time.min += minutes;
    if (current_time.min >= 60) {
        current_time.min -= 60;
        current_time.hour++;
    }

    current_time.hour += hours;
    if (current_time.hour >= 24) {
        current_time.hour -= 24; // Reiniciar las horas si exceden 24
    }

    printf("Final: %02d:%02d:%02d\n", current_time.hour, current_time.min, current_time.sec);

    // Configurar la alarma
    rtc_set_alarm(&current_time, &alarm_callback);
}

/**
 * @brief Callback que se ejecuta cuando se dispara la alarma.
 *
 * Activa la bandera `alarm_triggered` para indicar que la alarma se ha activado.
 */
void alarm_callback() {
    alarm_triggered = true; // Activar la bandera
}
