#ifndef SENSADO_AGUA_H
#define SENSADO_AGUA_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"


void init_adc(uint8_t adc_pin, uint8_t adc_channel);

float read_adc_voltage(uint8_t adc_channel);

#endif