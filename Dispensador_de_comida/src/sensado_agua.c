#include "sensado_agua.h"

// Función para inicializar el ADC
void init_adc(uint8_t adc_pin, uint8_t adc_channel)
{
    adc_init();
    adc_gpio_init(adc_pin);        // Configurar el pin GPIO como entrada ADC
    adc_select_input(adc_channel); // Seleccionar el canal correspondiente
}

// Función para leer el voltaje de un canal ADC
float read_adc_voltage(uint8_t adc_channel)
{
    adc_select_input(adc_channel); // Asegurarse de que se selecciona el canal correcto
    uint16_t raw = adc_read();     // Leer el valor crudo del ADC (0-4095)
    return raw * 3.3f / (1 << 12); // Convertir a voltaje (3.3V referencia)
}