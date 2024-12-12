#include "mostrar_en_displays.h"

// Pines de los segmentos y transistores
uint8_t display_pins[] = {10, 11, 12, 13, 18, 19, 20}; // A, B, C, D, E, F, G
uint8_t transistor_pins[] = {14, 15, 16, 17};          // Transistores para cada display

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

// Mapeo de las letras H, O, L, A en segmentos
uint8_t letter_map[] = {
    0b01110110, // H
    0b00111111, // O
    0b00111000, // L
    0b01110111  // A
};

/**
 * @brief Inicializa los pines de los segmentos y los transistores.
 * 
 * Configura los pines correspondientes a los segmentos de los displays de 7 segmentos
 * y los pines de control de los transistores para el multiplexado de los displays.
 */
void init_pins2()
{
    // Inicializar pines de los segmentos
    for (int i = 0; i < 7; i++) 
    {
        gpio_init(display_pins[i]);
        gpio_set_dir(display_pins[i], GPIO_OUT);
    }
    // Inicializar pines de los transistores
    for (int i = 0; i < 4; i++) 
    {
        gpio_init(transistor_pins[i]);
        gpio_set_dir(transistor_pins[i], GPIO_OUT);
    }
}

/**
 * @brief Muestra un dígito en un display específico.
 * 
 * Esta función configura los pines de los segmentos para mostrar el dígito especificado
 * en el display correspondiente, y activa el transistor asociado al display.
 *
 * @param digit El dígito a mostrar (0-9).
 * @param display El índice del display (0-3).
 */
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

/**
 * @brief Muestra un número de 4 dígitos en los displays.
 * 
 * La función descompone el número en 4 dígitos y los muestra en los displays de 7 segmentos,
 * multiplexando los displays rápidamente para hacer que todos sean visibles.
 *
 * @param number El número de 4 dígitos a mostrar (0-9999).
 */
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

/**
 * @brief Muestra una letra en un display específico.
 * 
 * Esta función muestra una letra (H, O, L, A) en un display de 7 segmentos,
 * activando los segmentos correspondientes de acuerdo con el mapeo de la letra.
 *
 * @param letter La letra a mostrar (debe ser una de las letras mapeadas: H, O, L, A).
 * @param display_index El índice del display (0-3) donde se mostrará la letra.
 */
void show_letter(uint8_t letter, uint8_t display_index) {
    // Activar los segmentos según el mapeo
    for (int i = 0; i < 7; i++) {
        gpio_put(display_pins[i], (letter >> i) & 1);
    }
    // Activar el transistor correspondiente al display
    for (int i = 0; i < 4; i++) {
        gpio_put(transistor_pins[i], i == display_index ? 1 : 0);
    }
}
