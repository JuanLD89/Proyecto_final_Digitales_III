#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definición de pines
#define SERVO_PIN 15 // Cambia al pin GPIO que estés usando

void set_servo_speed(uint slice_num, uint channel, float speed) {
    // Cálculo del ciclo de trabajo basado en la velocidad
    const float min_pulse_width_ms = 1.0f; // Velocidad máxima antihorario
    const float max_pulse_width_ms = 2.0f; // Velocidad máxima horario
    const float neutral_pulse_width_ms = 1.5f; // Detener

    float pulse_width_ms = neutral_pulse_width_ms +
                           speed * (speed > 0 ? (max_pulse_width_ms - neutral_pulse_width_ms)
                                              : (neutral_pulse_width_ms - min_pulse_width_ms));
    const float period_ms = 20.0f; // Periodo de PWM (50 Hz)
    float duty_cycle = (pulse_width_ms / period_ms) * 100.0f;

    uint16_t wrap = pwm_hw->slice[slice_num].top; // Usar el valor wrap configurado
    uint16_t level = (uint16_t)((duty_cycle / 100.0f) * wrap);

    pwm_set_chan_level(slice_num, channel, level); // Establecer el nivel de PWM
}

int main() {
    // Inicialización de la GPIO para PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN); // Obtener el slice del PWM
    uint channel = pwm_gpio_to_channel(SERVO_PIN);    // Obtener el canal

    // Configuración del PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 64.0f); // Divisor del reloj
    pwm_init(slice_num, &config, true);   // Iniciar el PWM con la configuración

    // Cálculo del valor máximo de contador (wrap) para 50 Hz (20 ms periodo)
    uint32_t sys_clk_freq = clock_get_hz(clk_sys);     // Obtener la frecuencia del reloj del sistema
    float pwm_clk_freq = sys_clk_freq / 64.0f;         // Frecuencia del reloj PWM con divisor
    uint16_t wrap = (uint16_t)(pwm_clk_freq / 50.0f) - 1; // Calcular wrap para 50 Hz
    pwm_set_wrap(slice_num, wrap); // Configurar el wrap calculado
    pwm_set_enabled(slice_num, true); // Habilitar el PWM

    bool motor = false; // Variable de control del motor

    while (true) {
        // Simulación de encendido del motor
        motor = true;

        if (motor) {
            set_servo_speed(slice_num, channel, 1.0f); // Máxima velocidad sentido horario
            sleep_ms(3000);                            // Mantener por 3 segundos
            set_servo_speed(slice_num, channel, -0.05f); // Detener el servo
            motor = false; // Resetear la variable
        }

        sleep_ms(5000);
    }

    return 0;
}
