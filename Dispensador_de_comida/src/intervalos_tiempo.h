#ifndef INTERVALO_TIEMPO_H
#define INTERVALO_TIEMPO_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "hardware/irq.h"
#include "hardware/sync.h"

// Variables externas para configurar intervalos
extern int alarm_interval_hours;
extern int alarm_interval_minutes;
extern int alarm_interval_seconds;
extern volatile bool alarm_triggered;


// Declaración de funciones
void rtc_set_alarm_in_interval(int hours, int minutes, int seconds);
void alarm_callback(void);


#endif // INTERVALO_TIEMPO_H