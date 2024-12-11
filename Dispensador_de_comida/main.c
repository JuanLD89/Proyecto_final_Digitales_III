#include "src/sensor_proximidad.h"
#include "src/intervalos_tiempo.h"
#include "src/configuracion_tiempo_teclado.h"
#include "src/mostrar_en_displays.h"
#include "src/configuracion_porcion_teclado.h"
#include "src/funcionamiento_motor.h"
#include "src/sensado_agua.h"

int main()
{
    stdio_init_all(); // Inicializar la consola
    init_pins();      // Configurar los pines
    init_pins2();
    setup();
    // Inicializar ADC en GPIO 26 (ADC 0)
    init_adc(28, 2);

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
    int porcion_por_segundo = 30; // gramos
    alarm_interval_hours = 4;     // Configurar horas
    alarm_interval_minutes = 0;   // Configurar minutos
    alarm_interval_seconds = 0;   // Configurar segundos

    // Captura el tiempo inicial para mostrar hola al inicio
    absolute_time_t start_time = get_absolute_time();
    const int duration_seconds = 3; // Duración en segundos

    while (true)
    {
        printf("Inicio del programa\n");

        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // mostrar hola al inicio
        if (inicio)
        {
            while (1)
            {
                // Verifica si el tiempo transcurrido supera la duración
                if (absolute_time_diff_us(start_time, get_absolute_time()) > duration_seconds * 1000000)
                {
                    break; // Sale del bucle después de 3 segundos
                }

                // Mostrar cada letra en su display correspondiente
                for (int i = 0; i < 4; i++)
                {
                    show_letter(letter_map[i], i);
                    sleep_ms(2); // Pequeña pausa para multiplexado
                }
            }

            // Apaga todos los displays al finalizar
            for (int i = 0; i < 4; i++)
            {
                gpio_put(transistor_pins[i], 0);
            }
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
            set_servo_speed(slice_num, channel, -1.5f); // Máxima velocidad sentido horario
            printf("milisegundos: %d\n", (porcion_por_segundo / 10)* 1000);
            sleep_ms((porcion_por_segundo / 10) * 1000);
            set_servo_speed(slice_num, channel, 0.15f); // Detener el servo
            sleep_ms(1000);

            float voltage = read_adc_voltage(2);
            printf("Voltage: %.2f V\n", voltage);

            if (voltage > 1)
            {
                gpio_put(MOTOBOMBA_PIN, 1);
                printf("milisegundos: %d\n", (porcion_por_segundo / 10)* 2000);
                sleep_ms((porcion_por_segundo / 10) * 2000);
                gpio_put(MOTOBOMBA_PIN, 0);
                sleep_ms(1000);
            }
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
                // configuracion porcion
                else if (key == 'B') // Inicia configuración
                {
                    char porcion[5] = {0}; // Buffer para la porción
                    configurar_porcion(porcion);
                    printf("Porción válida: %d gramos\n", gramos);
                    if (gramos < 10)
                    {
                        porcion_por_segundo = 10;
                    }
                    else
                    {
                        porcion_por_segundo = gramos;
                    }

                    key_pressed = false;
                    configuracion_alarma = true;
                }
                else if (key == 'C')
                {
                    // ejecucion
                    set_servo_speed(slice_num, channel, -1.5f);  // Máxima velocidad sentido horario
                    printf("milisegundos: %d\n", (porcion_por_segundo / 10)* 1000);
                    sleep_ms((porcion_por_segundo / 10) * 1000); 
                    set_servo_speed(slice_num, channel, 0.15f);  // Detener el servo
                    sleep_ms(1000);
                    key_pressed = false;
                    configuracion_alarma = false;
                }
                else if (key == 'D')
                {
                    float voltage = read_adc_voltage(2);
                    printf("Voltage: %.2f V\n", voltage);
                    if (voltage > 1)
                    {
                        gpio_put(MOTOBOMBA_PIN, 1);
                        printf("milisegundos: %d\n", (porcion_por_segundo / 10)*2000);
                        sleep_ms((porcion_por_segundo / 10) * 2000);
                        gpio_put(MOTOBOMBA_PIN, 0);
                        sleep_ms(1000);
                    }
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