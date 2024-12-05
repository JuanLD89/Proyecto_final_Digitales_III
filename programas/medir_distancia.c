#include <stdio.h>
#include "pico/stdlib.h"

#define ECHO_PIN 26
#define TRIGGER_PIN 27

// Configuración de pines
void init_pins() {
    gpio_init(TRIGGER_PIN);
    gpio_set_dir(TRIGGER_PIN, GPIO_OUT);
    gpio_put(TRIGGER_PIN, 0);

    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
}

// Medir el pulso en alto
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

// Función para medir distancia
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

// Programa principal
int main() {
    stdio_init_all(); // Inicializar la consola
    init_pins();      // Configurar los pines

    printf("Iniciando medición de distancia...\n");

    while (true) {
        float distancia = medir_distancia();
        if (distancia > 0 && distancia < 30) {
            printf("Distancia: %.1f cm\n", distancia);
        } else {
            printf("Error en la medición o fuera de rango.\n");
        }
        sleep_ms(1000); 
    }

    return 0;
}
