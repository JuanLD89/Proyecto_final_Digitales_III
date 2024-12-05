#include "mostrar_en_displays.h"

// Pines de los segmentos y transistores
uint8_t display_pins[] = {21, 28, 13, 12, 11, 20, 10}; // A, B, C, D, E, F, G
uint8_t transistor_pins[] = {17, 16, 18, 19};          // Transistores para cada display

// Mapeo de los números 0-9 en segmentos de 7 segmentos
uint8_t segment_map[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

// Inicialización de los pines de salida
void init_pins2()
{
    for (int i = 0; i < 7; i++) // Inicializar pines de los segmentos
    {
        gpio_init(display_pins[i]);
        gpio_set_dir(display_pins[i], GPIO_OUT);
    }
    for (int i = 0; i < 4; i++) // Inicializar pines de los transistores
    {
        gpio_init(transistor_pins[i]);
        gpio_set_dir(transistor_pins[i], GPIO_OUT);
    }
}

// Mostrar un dígito en un display específico
void show_digit(uint8_t digit, uint8_t display)
{
    // Apagar todos los transistores para evitar superposición
    for (int i = 0; i < 4; i++)
    {
        gpio_put(transistor_pins[i], 0);
    }

    // Configurar los pines de los segmentos para mostrar el dígito
    uint8_t segments = segment_map[digit];
    for (int i = 0; i < 7; i++)
    {
        gpio_put(display_pins[i], (segments >> i) & 1);
    }

    // Encender el transistor correspondiente al display
    gpio_put(transistor_pins[display], 1);

    // Esperar para que el dígito sea visible antes de apagarlo
    sleep_ms(2);

    // Apagar el transistor del display
    gpio_put(transistor_pins[display], 0);
}

// Mostrar un número en los 4 displays
void show_number(int number)
{
    uint8_t digits[4] = {
        (number / 1000) % 10, // Milésimas
        (number / 100) % 10,  // Centésimas
        (number / 10) % 10,   // Decenas
        number % 10           // Unidades
    };

    // Multiplexar los 4 displays rápidamente
    for (int i = 0; i < 4; i++)
    {
        show_digit(digits[i], i);
    }
}
