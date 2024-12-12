#ifndef SENSADO_AGUA_H
#define SENSADO_AGUA_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

/**
 * @brief Inicializa el ADC en un pin y canal específicos.
 * 
 * Esta función configura el ADC para leer un valor del pin GPIO especificado
 * y selecciona el canal correspondiente para realizar la conversión de la señal analógica.
 *
 * @param adc_pin Pin GPIO para el ADC (por ejemplo, un pin de la Raspberry Pi Pico).
 * @param adc_channel Canal ADC correspondiente al pin especificado (0-3).
 */
void init_adc(uint8_t adc_pin, uint8_t adc_channel);

/**
 * @brief Lee el voltaje de un canal ADC específico.
 * 
 * Lee el valor crudo de un canal ADC y lo convierte a un voltaje en función de la referencia de 3.3V.
 *
 * @param adc_channel Canal ADC del cual se leerá el valor.
 * @return El voltaje medido en el canal ADC especificado.
 */
float read_adc_voltage(uint8_t adc_channel);

#endif // SENSADO_AGUA_H
