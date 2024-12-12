/**
 * @file intervalo_tiempo.h
 * @brief Declaraciones para manejar intervalos de tiempo y alarmas en el RTC.
 */

#ifndef INTERVALO_TIEMPO_H
#define INTERVALO_TIEMPO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "hardware/irq.h"
#include "hardware/sync.h"

// Variables externas para configurar intervalos
extern int alarm_interval_hours;    ///< Horas del intervalo de la alarma.
extern int alarm_interval_minutes;  ///< Minutos del intervalo de la alarma.
extern int alarm_interval_seconds;  ///< Segundos del intervalo de la alarma.
extern volatile bool alarm_triggered; ///< Bandera para indicar si la alarma se activó.

/**
 * @brief Configura una alarma en el RTC después de un intervalo específico.
 *
 * Esta función permite sumar un intervalo de tiempo definido (horas, minutos y segundos) 
 * al tiempo actual y establece una alarma que se activa al cumplirse ese intervalo.
 *
 * @param hours Número de horas que se sumarán al tiempo actual.
 * @param minutes Número de minutos que se sumarán al tiempo actual.
 * @param seconds Número de segundos que se sumarán al tiempo actual.
 */
void rtc_set_alarm_in_interval(int hours, int minutes, int seconds);

/**
 * @brief Callback que se ejecuta al dispararse la alarma del RTC.
 *
 * Esta función se activa automáticamente cuando la alarma configurada en el RTC se cumple. 
 */
void alarm_callback(void);

#endif // INTERVALO_TIEMPO_H
