#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define DEBOUNCE_DELAY_MS 150 // Tiempo de debounce en milisegundos
#define MAX_CLAVE_LENGTH 4

const uint LedRojo = 14;
const uint LedVerde = 15;

// Pines del teclado
uint columns[4] = {2, 5, 4, 3};
uint rows[4] = {9, 8, 7, 6};

char claveActual[MAX_CLAVE_LENGTH + 1] = "1111";

// Valores de la matriz de teclas
char keys[16] = {'1', '2', '3', 'A',
                 '4', '5', '6', 'B',
                 '7', '8', '9', 'C',
                 '*', '0', '#', 'D'};

// Variables internas para almacenamiento
uint _columns[4];
uint _rows[4];
char _matrix_values[16];
uint all_columns_mask = 0x0;
uint column_mask[4];
absolute_time_t last_press_time; // Para el control de debounce

// Variable global para almacenar la tecla presionada
char key_pressed = '\0';

// Inicializa el teclado matricial
void pico_keypad_init(uint columns[4], uint rows[4], char matrix_values[16]) {
    for (int i = 0; i < 16; i++) {
        _matrix_values[i] = matrix_values[i];
    }

    for (int i = 0; i < 4; i++) {
        _columns[i] = columns[i];
        _rows[i] = rows[i];

        gpio_init(_columns[i]);
        gpio_init(_rows[i]);

        gpio_set_dir(_columns[i], GPIO_IN);
        gpio_set_dir(_rows[i], GPIO_OUT);

        gpio_pull_down(_columns[i]);
        gpio_put(_rows[i], 1);

        all_columns_mask |= (1 << _columns[i]);
        column_mask[i] = 1 << _columns[i];
    }
}

// Escanea el teclado y devuelve la tecla presionada
char pico_keypad_get_key(void) {
    uint32_t cols;
    int row;

    cols = gpio_get_all() & all_columns_mask;
    if (cols == 0x0) {
        return 0;
    }

    for (int j = 0; j < 4; j++) {
        gpio_put(_rows[j], 0);
    }

    for (row = 0; row < 4; row++) {
        gpio_put(_rows[row], 1);
        busy_wait_us(10000); // Evita rebotes
        cols = gpio_get_all() & all_columns_mask;
        gpio_put(_rows[row], 0);

        if (cols != 0x0) {
            break;
        }
    }

    for (int i = 0; i < 4; i++) {
        gpio_put(_rows[i], 1);
    }

    for (int i = 0; i < 4; i++) {
        if (cols == column_mask[i]) {
            return _matrix_values[row * 4 + i];
        }
    }

    return 0;
}

// Configura interrupciones para el teclado
void pico_keypad_irq_enable(bool enable, gpio_irq_callback_t callback) {
    for (int i = 0; i < 4; i++) {
        gpio_set_irq_enabled_with_callback(_columns[i], GPIO_IRQ_EDGE_RISE, enable, callback);
    }
}

// Función de callback de interrupción con debounce
void key_pressed_callback(uint gpio, uint32_t events) {
    absolute_time_t current_time = get_absolute_time();
    if (absolute_time_diff_us(last_press_time, current_time) < DEBOUNCE_DELAY_MS * 1000) {
        return; // Ignorar si el tiempo de debounce no ha pasado
    }

    last_press_time = current_time; // Actualizar tiempo de la última pulsación

    char key = pico_keypad_get_key();
    if (key) {
        key_pressed = key; // Asignar la tecla presionada a la variable global
        printf("Presionaste: %c\n", key);
    }
}

int verificarUsuario(const char *clave, const char *claveActual)
{
    if (strcmp(claveActual, clave) == 0)
    {
        return 1; // Usuario verificado
    }
    return 0; // Verificación fallida
}

void encenderLedVerde()
{
    printf("Acceso concedido.\n");
    gpio_put(LedVerde, 1);
    sleep_ms(5000);
    gpio_put(LedVerde, 0);
    sleep_ms(500);
}

void encenderLedRojo()
{
    printf("Acceso denegado.\n");
    gpio_put(LedRojo, 1);
    sleep_ms(2000); //2 segundos prendido (tiempo para indicar clave erronea)
    gpio_put(LedRojo, 0);
    sleep_ms(500);
}

int manejarAutenticacion(char *tempClave)
{

    printf("Ingrese la clave:\n");
    int claveComplete = 0;
    absolute_time_t last_change_time = get_absolute_time();
    const uint32_t interval = 1000 * 1000; // 1 segundo en microsegundos
    while (1)
    {

        char key = key_pressed;
        if (key != '\0')
        {
            if (!claveComplete && strlen(tempClave) < MAX_CLAVE_LENGTH)
            {
                strncat(tempClave, &key, 1); // Añade un solo carácter a la clave
                key_pressed = '\0';
                if (strlen(tempClave) == MAX_CLAVE_LENGTH)
                {
                    claveComplete = 1; // Clave completa
                }
            }
        }

        if (claveComplete)
        {
            break; // Salir si se completo la clave
        }
    }

    printf("Clave ingresada: %s\n", tempClave);

    if (verificarUsuario(tempClave, claveActual))
    {
        encenderLedVerde();
        return 1; // Autenticación exitosa
    }
    else
    {
        encenderLedRojo();
        return 0; // Falló la autenticación
    }

}

void cambiarClave(char *claveActual)
{
    char nuevaClave[MAX_CLAVE_LENGTH + 1] = {0};

    // Leer la nueva clave usando el teclado matricial
    printf("Ingrese la nueva clave:\n");

    time_t start = time(NULL);
    time_t end;
    int claveComplete = 0;
    gpio_put(LedVerde, 1);
    gpio_put(LedRojo, 1);
    absolute_time_t last_change_time = get_absolute_time();
    const uint32_t interval = 1000 * 1000; // 1 segundo en microsegundos

    while (1)
    {
        if (absolute_time_diff_us(last_change_time, get_absolute_time()) >= interval)
        {
            last_change_time = get_absolute_time();
        }
        end = time(NULL);
        if (difftime(end, start) >= 10)
        { // Tiempo máximo de entrada
            printf("Tiempo agotado. No se cambió la clave.\n");
            gpio_put(LedVerde, 0);
            gpio_put(LedRojo, 0);
            sleep_ms(100);
            encenderLedRojo();
            return;
        }

        char key = key_pressed;
        if (key != '\0')
        {
            if (strlen(nuevaClave) < MAX_CLAVE_LENGTH)
            {
                strncat(nuevaClave, &key, 1); // Añade un solo carácter a la nueva clave
                key_pressed = '\0';
                if (strlen(nuevaClave) == MAX_CLAVE_LENGTH)
                {
                    claveComplete = 1; // Clave completa
                }
            }
        }

        if (claveComplete)
        {
            break; // Salir si se completó la nueva clave
        }
    }
    printf("Nueva clave ingresada: %s\n", nuevaClave); // Mostrar clave parcial

    strcpy(claveActual, nuevaClave);
    printf("Clave cambiada exitosamente.\n");
    gpio_put(LedVerde, 0);
    gpio_put(LedRojo, 0);
    sleep_ms(100);
    encenderLedVerde();
}

int main() {
    stdio_init_all();
    last_press_time = get_absolute_time(); // Inicializar tiempo de última pulsación
    pico_keypad_init(columns, rows, keys);
    pico_keypad_irq_enable(true, key_pressed_callback);

    // Configura el pin como salida
    gpio_init(LedRojo);
    gpio_set_dir(LedRojo, GPIO_OUT);
    gpio_init(LedVerde);
    gpio_set_dir(LedVerde, GPIO_OUT);

    while (1) {
        char tempClave[MAX_CLAVE_LENGTH + 1] = {0};
        if (key_pressed != '\0') {
            if (key_pressed == '*')
            {
                key_pressed = '\0'; // Resetear la variable después de imprimir
                    if (manejarAutenticacion(tempClave))
                    {
                        printf("Usuario autenticado.\n");
                        key_pressed = '\0'; // Resetear la variable después de imprimir
                    }
                    else
                    {
                        printf("Fallo en la autenticación.\n");
                        key_pressed = '\0'; // Resetear la variable después de imprimir
                    }
            }
            else if (key_pressed == '#')
            {
                key_pressed = '\0';
                if (manejarAutenticacion(tempClave))
                {
                    printf("Clave correcta.\n");
                    cambiarClave(claveActual);
                    key_pressed = '\0';
                }
                else
                {
                    printf("Clave incorrecta.\n");
                    key_pressed = '\0';
                }
            }
            else
            {
                key_pressed = '\0';
            }
        }

        sleep_ms(100); // Evitar uso excesivo de CPU
    }
}
