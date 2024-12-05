#include "src/sensor_proximidad.h"
#include "src/intervalos_tiempo.h"
#include "src/configuracion_tiempo_teclado.h"

int main()
{
    stdio_init_all(); // Inicializar la consola
    init_pins();      // Configurar los pines
    setup();

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

    bool medir = false;
    alarm_interval_hours = 0;    // Configurar horas
    alarm_interval_minutes = 0;  // Configurar minutos
    alarm_interval_seconds = 0; // Configurar segundos

    printf("Inicio del programa\n");

    while (true)
    {
        printf("Inicio del programa\n");

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Medir distancia para la comida
        if (medir == true)
        {
            float distancia = medir_distancia();
            if (distancia > 0 && distancia < 30)
            {
                printf("Distancia: %.1f cm\n", distancia);
            }
            else
            {
                printf("Error en la medición o fuera de rango.\n");
            }
            sleep_ms(1000);
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        // Configurar la alarma
        rtc_set_alarm_in_interval(alarm_interval_hours, alarm_interval_minutes, alarm_interval_seconds);

        // Entrar en espera hasta que la alarma se active
        while (!alarm_triggered && !key_pressed)
        {
            __wfi();
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (alarm_triggered)
        {
            // La alarma se activo, realizar accion
            alarm_triggered = false;
            // ejecucion
            for (int i = 0; i < 5; i++)
            {
                printf("Ejecucion...\n");
                sleep_ms(500);
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        while(key_pressed)
        {
            // Leer la tecla presionada
            char key = scanKeypad();
            if (key != '\0')
            {
                printf("Tecla presionada: %c\n", key);

                //configurar hora
                if (key == 'A') // Inicia configuración
                {
                    char horas[3] = {0};   // Buffer para horas
                    char minutos[3] = {0}; // Buffer para minutos
                    configurar_hora(horas, minutos);
                    int horas_int = atoi(horas);
                    int minutos_int = atoi(minutos);
                    printf("Hora configurada: %d:%d\n", horas_int, minutos_int);
                    alarm_interval_hours = horas_int;    // Configurar horas
                    alarm_interval_minutes = minutos_int;  // Configurar minutos
                    alarm_interval_seconds = 0; // Configurar segundos
                    // Restablecer la bandera
                    key_pressed = false;
                }
                 if (key == 'D')
                 {
                    // Restablecer la bandera
                    key_pressed = false;
                 }
            }
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    return 0;
}