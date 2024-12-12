/**
 * @file configuracion_porcion_teclado.c
 * @brief Configura la porción en gramos usando teclado matricial.
 *
 * Este archivo contiene la implementación de la función que permite configurar
 * la cantidad en gramos para el dispensador de comida a través del teclado matricial. 
 * La cantidad ingresada se valida y se muestra en el display.
 */

#include "configuracion_porcion_teclado.h"

// Variables globales
int gramos = 0; ///< Variable global que almacena la porción configurada en gramos.
int gramos0 = 0; ///< Variable global para la visualización de la porción durante la configuración.

/**
 * @brief Configura la cantidad de gramos utilizando el teclado matricial.
 *
 * Esta función permite capturar y validar la entrada del usuario para establecer
 * la cantidad de gramos deseada. Se aceptan valores numéricos de hasta 4 dígitos.
 * El proceso termina cuando se presiona el carácter '#' tras ingresar un valor válido.
 *
 * @param[in,out] porcion Arreglo de caracteres que almacena temporalmente la entrada del usuario.
 */
void configurar_porcion(char *porcion)
{
    int i = 0; ///< Variable que recorre el arreglo `porcion`.
    bool porcion_completada = false; ///< Indicador de si la porción se configuró correctamente.

    printf("Configuración de porción en gramos:\n");

    while (true)
    {
        // Leer una tecla del teclado matricial
        char key = scanKeypad();
        
        // Validar si la tecla es un número
        if (key != '\0' && key >= '0' && key <= '9') // Solo números
        {
            porcion[i++] = key; ///< Almacenar la tecla ingresada en el arreglo.
            gramos0 = atoi(porcion); ///< Convertir la entrada actual a un número entero.
            printf("Porción: %d\n", gramos0);

            // Validar si se alcanzaron 4 dígitos
            if (i == 4)
            {
                porcion[4] = '\0'; ///< Asegurar que la cadena termine correctamente.
                gramos = atoi(porcion); ///< Convertir la entrada completa a un número entero.

                // Validar que la porción esté en el rango permitido
                if (gramos >= 0 && gramos <= 9999)
                {
                    porcion_completada = true;
                }
                else
                {
                    gramos0 = 0; ///< Reiniciar el valor mostrado si la entrada es inválida.
                    printf("Porción inválida, reiniciando...\n");
                }

                // Reiniciar el índice para capturar una nueva entrada
                i = 0;
                memset(porcion, 0, sizeof(char) * 5); ///< Limpiar el arreglo `porcion`.
            }
        }

        // Mostrar la cantidad actual en el display
        show_number(gramos0);

        // Finalizar si la porción fue configurada y se presiona '#'
        if (porcion_completada && key == '#')
        {
            break;
        }
    }
}
