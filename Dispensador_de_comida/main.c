#include "src/sensor_proximidad.h"
#include "src/intervalos_tiempo.h"
#include "src/configuracion_tiempo_teclado.h"
#include "src/mostrar_en_displays.h"
#include "src/configuracion_porcion_teclado.h"
#include "src/funcionamiento_motor.h"

int main()
{
    stdio_init_all(); // Inicializar la consola
    init_pins();      // Configurar los pines
    init_pins2();
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
    uint slice_num, channel;
    init_servo(&slice_num, &channel);

    bool medir = false;
    bool inicio = true;
    bool configuracion_alarma = true;
    alarm_interval_hours = 0;    // Configurar horas
    alarm_interval_minutes = 0;  // Configurar minutos
    alarm_interval_seconds = 20; // Configurar segundos

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
        if (configuracion_alarma)
        {
            // Configurar la alarma
            rtc_set_alarm_in_interval(alarm_interval_hours, alarm_interval_minutes, alarm_interval_seconds);
        }
        

        // Entrar en espera hasta que la alarma se active
        while (!alarm_triggered && !key_pressed)
        {
            __wfi();
        }
        configuracion_alarma = true;
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (alarm_triggered)
        {
            // La alarma se activo, realizar accion
            alarm_triggered = false;
            // ejecucion
            set_servo_speed(slice_num, channel, -1.0f);   // Máxima velocidad sentido horario
            sleep_ms(3000);                              // Mantener por 3 segundos
            set_servo_speed(slice_num, channel, 0.094f); // Detener el servo
            sleep_ms(1000);
            gpio_put(MOTOBOMBA_PIN, 1);
            sleep_ms(3000);
            gpio_put(MOTOBOMBA_PIN, 0);
            sleep_ms(1000);
            key_pressed = false;
        }
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        while (key_pressed)
        {
            // Leer la tecla presionada
            char key = scanKeypad();
            if (key != '\0')
            {
                printf("Tecla presionada: %c\n", key);

                // configurar hora
                if (key == 'A') // Inicia configuración
                {
                    char horas[3] = {0};   // Buffer para horas
                    char minutos[3] = {0}; // Buffer para minutos
                    configurar_hora(horas, minutos);
                    int horas_int = atoi(horas);
                    int minutos_int = atoi(minutos);
                    printf("Hora configurada: %d:%d\n", horas_int, minutos_int);
                    alarm_interval_hours = horas_int;     // Configurar horas
                    alarm_interval_minutes = minutos_int; // Configurar minutos
                    alarm_interval_seconds = 0;           // Configurar segundos
                    // Restablecer la bandera
                    key_pressed = false;
                    configuracion_alarma = true;
                }
                //configuracion porcion
                else if (key == 'B') // Inicia configuración
                {
                    char porcion[5] = {0}; // Buffer para la porción
                    configurar_porcion(porcion);
                    printf("Porción válida: %d gramos\n", gramos);
                    key_pressed = false;
                    configuracion_alarma = true;
                }
                else if (key == 'C'){
                    // ejecucion
                    set_servo_speed(slice_num, channel, 1.0f);   // Máxima velocidad sentido horario
                    sleep_ms(3000);                              // Mantener por 3 segundos
                    set_servo_speed(slice_num, channel, 0.05f); // Detener el servo
                    key_pressed = false;
                    configuracion_alarma = false;
                }
                else if (key == 'D')
                {
                    gpio_put(MOTOBOMBA_PIN, 1);
                    sleep_ms(3000);
                    gpio_put(MOTOBOMBA_PIN, 0);
                    sleep_ms(1000);
                    key_pressed = false;
                    configuracion_alarma = false;
                }
                
                else if (key == '#')
                {
                    // Restablecer la bandera
                    key_pressed = false;
                    configuracion_alarma = false;
                }
            }
            if (inicio)
            {
                // Restablecer la bandera
                key_pressed = false;
                inicio = false;
                break;
            }
            sleep_ms(100);
        }

        //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    return 0;
}