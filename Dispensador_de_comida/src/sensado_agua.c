#include "sensado_agua.h"

/**
 * @brief Inicializa el ADC en un pin y canal.
 *
 * Configura el ADC para que pueda leer valores de un pin GPIO especificado
 * y seleccionar el canal correspondiente para la lectura del sensor de agua.
 *
 * @param adc_pin Pin GPIO para el ADC.
 * @param adc_channel Canal ADC correspondiente al pin especificado.
 */
void init_adc(uint8_t adc_pin, uint8_t adc_channel)
{
    adc_init();                    ///< Inicializa el ADC
    adc_gpio_init(adc_pin);         ///< Configura el pin GPIO como entrada ADC
    adc_select_input(adc_channel);  ///< Selecciona el canal ADC correspondiente
}

/**
 * @brief Lee el voltaje de un canal ADC específico.
 *
 * Esta función lee el valor crudo del ADC y lo convierte en un voltaje correspondiente
 * utilizando la referencia de 3.3V para realizar la conversión a voltaje.
 *
 * @param adc_channel Canal ADC del cual se lee el valor.
 * @return Voltaje correspondiente a la lectura del canal ADC.
 */
float read_adc_voltage(uint8_t adc_channel)
{
    adc_select_input(adc_channel); ///< Asegura que el canal correcto esté seleccionado
    uint16_t raw = adc_read();     ///< Lee el valor crudo del ADC
    return raw * 3.3f / (1 << 12); ///< Convierte el valor crudo a voltaje (3.3V referencia)
}
