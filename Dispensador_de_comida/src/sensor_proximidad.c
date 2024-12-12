/**
 * @file sensor_proximidad.h
 * @brief Implementación para medir distancias usando un sensor de proximidad.
 */

#include "sensor_proximidad.h"

/**
 * @brief Configura los pines para el sensor de proximidad.
 *
 * Inicializa el pin TRIGGER como salida y el pin ECHO como entrada.
 */
void init_pins() {
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_put(TRIGGER_PIN, 0);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

/**
 * @brief Mide la duración de un pulso en alto en un pin GPIO.
 *
 * Esta función mide el tiempo que el pin especificado permanece en estado alto.
 *
 * @param pin Pin GPIO en el que se mide el pulso.
 * @return Duración del pulso en microsegundos.
 */
uint32_t measure_pulse_high(uint pin) {
    uint32_t start_time = 0, end_time = 0;

    // Esperar a que el pin esté en bajo antes de empezar
    while (gpio_get(pin) == 1);

    // Esperar hasta que el pin suba
    while (gpio_get(pin) == 0);
    start_time = time_us_32();

    // Esperar hasta que el pin baje
    while (gpio_get(pin) == 1);
    end_time = time_us_32();

    return end_time - start_time;
}

/**
 * @brief Mide la distancia utilizando un sensor.
 *
 * Esta función genera un pulso de disparo (trigger) para activar el sensor
 * y mide la duración del pulso en alto del pin ECHO. Calcula la distancia
 * en función del tiempo medido.
 *
 * @return Distancia medida en centímetros.
 */
float medir_distancia() {
    // Generar el pulso de trigger
    gpio_put(TRIGGER_PIN, 0);
    sleep_us(2);
    gpio_put(TRIGGER_PIN, 1);
    sleep_us(10);
    gpio_put(TRIGGER_PIN, 0);

    // Medir la duración del pulso en alto del pin ECHO
    uint32_t duracion = measure_pulse_high(ECHO_PIN);

    // Calcular distancia en cm
    float distancia = (duracion * 0.034) / 2.0;
    return distancia;
}
