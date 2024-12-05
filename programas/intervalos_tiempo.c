#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/rtc.h"
#include "pico/util/datetime.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
// Variables configurables para el intervalo
int alarm_interval_hours = 0;    // Configurar horas
int alarm_interval_minutes = 0; // Configurar minutos
int alarm_interval_seconds = 0; // Configurar segundos
volatile bool alarm_triggered = false; // Bandera para indicar que la alarma se activó
// Prototipo de funciones
void rtc_set_alarm_in_interval(int hours, int minutes, int seconds);
void alarm_callback();
// Función para configurar la alarma en el RTC
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
// Callback que se ejecuta al dispararse la alarma
void alarm_callback() {
    alarm_triggered = true; // Activar la bandera
}
int main() {
    stdio_init_all();
    // Inicializar el RTC
    datetime_t t = {
        .year = 2024,
        .month = 12,
        .day = 2,
        .hour = 0,
        .min = 0,
        .sec = 0,
    };
    rtc_init();
    rtc_set_datetime(&t);
    printf("Inicio.\n");
    alarm_interval_hours = 0;    // Configurar horas
    alarm_interval_minutes = 1; // Configurar minutos
    alarm_interval_seconds = 0; // Configurar segundos
    while (true) {
        // Configurar la alarma
        rtc_set_alarm_in_interval(alarm_interval_hours, alarm_interval_minutes, alarm_interval_seconds);
        // Entrar en espera hasta que la alarma se active
        while (!alarm_triggered) {
            __wfi();
        }
        // La alarma se activo, realizar accion
        alarm_triggered = false; 
        
        //ejecucion
        for (int i = 0; i < 5; i++) {
            printf("Ejecucion...\n");
            sleep_ms(500);
        }
    }
    return 0;
}
