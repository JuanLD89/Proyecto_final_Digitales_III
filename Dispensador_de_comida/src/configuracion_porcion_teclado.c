#include "configuracion_porcion_teclado.h"

int gramos = 0; // Variable para almacenar la porción en gramos
int gramos0 = 0;

// Configurar la porción
void configurar_porcion(char *porcion)
{
    int i = 0;
    bool porcion_completada = false;

    printf("Configuración de porción en gramos:\n");

    while (true)
    {
        char key = scanKeypad();
        if (key != '\0' && key >= '0' && key <= '9') // Solo números
        {
            porcion[i++] = key;
            gramos0 = atoi(porcion);
            printf("Porción: %d\n", gramos0);

            if (i == 4) // Máximo 4 dígitos (9999)
            {
                porcion[4] = '\0'; // Aseguramos el fin de cadena
                gramos = atoi(porcion);

                if (gramos >= 0 && gramos <= 9999)
                {
                    porcion_completada = true;
                }
                else
                {
                    gramos0 = 0;
                    printf("Porción inválida, reiniciando...\n");
                }

                i = 0; // Reiniciar para capturar otra entrada
                memset(porcion, 0, sizeof(char) * 5);
            }
        }
        show_number(gramos0);
        if (porcion_completada && key == '#')
        {   
            break;
        }
        
    }
}
