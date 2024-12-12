#include "funcionamiento_motor.h"

/**
 * @brief Inicializa el servo motor y la motobomba.
 *
 * Configura el pin asociado al servo motor para operar en modo PWM,
 * ajusta la frecuencia del PWM a 50 Hz y configura el pin de la
 * motobomba como salida digital.
 *
 * @param slice_num Puntero a la variable donde se almacenará el número de slice del PWM.
 * @param channel Puntero a la variable donde se almacenará el canal del PWM.
 */
void init_servo(uint *slice_num, uint *channel) {
    // Configuración de la GPIO para PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    *slice_num = pwm_gpio_to_slice_num(SERVO_PIN); // Obtener el slice del PWM
    *channel = pwm_gpio_to_channel(SERVO_PIN);    // Obtener el canal

    // Configuración del PWM
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 64.0f); // Divisor del reloj
    pwm_init(*slice_num, &config, true);   // Iniciar el PWM con la configuración

    // Calcular y configurar el valor máximo del contador (wrap) para 50 Hz (20 ms periodo)
    uint32_t sys_clk_freq = clock_get_hz(clk_sys);     // Frecuencia del reloj del sistema
    float pwm_clk_freq = sys_clk_freq / 64.0f;         // Frecuencia del reloj PWM con divisor
    uint16_t wrap = (uint16_t)(pwm_clk_freq / 50.0f) - 1; // Wrap para 50 Hz
    pwm_set_wrap(*slice_num, wrap); // Configurar el wrap calculado
    pwm_set_enabled(*slice_num, true); // Habilitar el PWM

    // Configuración de la motobomba como salida digital
    gpio_init(MOTOBOMBA_PIN);
    gpio_set_dir(MOTOBOMBA_PIN, GPIO_OUT);
    gpio_put(MOTOBOMBA_PIN, 0); // LED apagado inicialmente
}

/**
 * @brief Configura la velocidad del servo motor.
 *
 * Ajusta el ancho de pulso del PWM para controlar la velocidad y dirección del servo motor.
 *
 * @param slice_num Número del slice asociado al pin del servo motor.
 * @param channel Canal del PWM asociado al pin del servo motor.
 * @param speed Velocidad deseada del servo motor, en un rango de -1.0 a 1.0:
 *              - -1.0: Velocidad máxima antihoraria.
 *              -  0.0: Posición neutral (detenido).
 *              -  1.0: Velocidad máxima horaria.
 */
void set_servo_speed(uint slice_num, uint channel, float speed) {
    // Cálculo del ciclo de trabajo basado en la velocidad
    const float min_pulse_width_ms = 1.0f; // Velocidad máxima antihoraria
    const float max_pulse_width_ms = 2.0f; // Velocidad máxima horaria
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
