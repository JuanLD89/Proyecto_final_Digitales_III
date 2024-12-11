cmake_minimum_required(VERSION 3.13)

# Always include it
include(pico_sdk_import.cmake)

# Project's name (Replace Dispensador_de_comida with your own project's name)
project(Dispensador_de_comida)

# SDK Initialization - Mandatory
pico_sdk_init()

# C/C++ project files
add_executable(Dispensador_de_comida
    main.c
    src/sensor_proximidad.c
    src/sensor_proximidad.h
    src/intervalos_tiempo.c
    src/intervalos_tiempo.h
    src/configuracion_tiempo_teclado.c
    src/configuracion_tiempo_teclado.h
    src/mostrar_en_displays.c
    src/mostrar_en_displays.h
    src/configuracion_porcion_teclado.c
    src/configuracion_porcion_teclado.h
    src/funcionamiento_motor.c
    src/funcionamiento_motor.h
    src/sensado_agua.c
    src/sensado_agua.h
)

# pico_stdlib library. You can add more if they are needed
target_link_libraries(Dispensador_de_comida pico_stdlib hardware_pwm hardware_clocks hardware_rtc hardware_adc)

# Enable usb output, disable uart output
pico_enable_stdio_usb(Dispensador_de_comida 1)
pico_enable_stdio_uart(Dispensador_de_comida 0)

# Need to generate UF2 file for upload to RP2040
pico_add_extra_outputs(Dispensador_de_comida)
