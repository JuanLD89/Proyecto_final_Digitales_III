# Proyecto_final_Digitales_III
Proyecto de un dispensador de comida inteligente para mascotas con Raspberry Pi Pico. Automatiza la alimentación mediante horarios programables y detección de niveles de comida y agua. Incluye opciones de dispensado manual y teclado para configuración.

-- Nombre del proyecto. 

    - Happy pet!!

-- Idea de proyecto final.

    - El proyecto consiste en la creación de un dispensador de comida inteligente para mascotas, utilizando la Raspberry Pi Pico como unidad de control principal. Este dispositivo tiene como objetivo 
      proporcionar una solución automatizada para la alimentación de mascotas, permitiendo que reciban su comida de manera regular y en cantidades controladas, incluso cuando los dueños no están presentes.
        
    - Una característica clave del dispensador es su capacidad para detectar los niveles de comida restantes en el compartimento de almacenamiento. Si se detecta que el nivel es bajo y coincide con el horario          programado para la alimentación, el dispositivo liberará la cantidad necesaria de comida para evitar que se derrame. De esta manera, se garantiza que la comida se distribuya de manera precisa y controlada.
        
    - También se pondrá un teclado matricial que controle el bloqueo al compartimento de almacenamiento, configuración de hora de dispensado y de proporciones.

-- Requisitos funcionales.

     - Automatización de la Alimentación:
          El sistema permitirá la programación de horarios para la dispensación de comida mediante el teclado matricial.
          Deberá ser capaz de configurar la cantidad de comida a dispensar para cada horario programado.
          
     - Detección de Niveles de Comida:
          El sistema deberá medir el nivel de comida restante en el compartimento utilizando un sensor.
          Si el nivel de comida es bajo y coincide con un horario de dispensado, deberá liberar solo la cantidad necesaria para evitar derrames.
          
     - Dispensación Precisa de Comida:
          Deberá liberar una cantidad específica de comida de acuerdo con la configuración establecida para cada ciclo de alimentación.
          El sistema deberá detener el motor automáticamente al alcanzar la cantidad deseada.
          
     - Configuración de Parámetros con Teclado Matricial:
          El sistema permite al usuario ajustar los horarios de dispensado de comida mediante el teclado matricial.
          Se podrá configurar las proporciones de comida que se dispensarán en cada ciclo de alimentación.
          Se podrá controlar el bloqueo y desbloqueo del compartimento de almacenamiento mediante el teclado, para asegurar el acceso seguro a la comida.
          
      - Medición de Nivel de Agua:
          El sistema mide el nivel de agua disponible en el compartimento de agua mediante un sensor.
          
      - Opción de dispensado manual: 
          El usuario puede dispensar manualmente la comida, independientemente de la programación automática de horarios. Esto le permitirá al usuario proporcionar comida adicional a la mascota en caso de ser             necesario.

-- Requisitos NO funcionales.

     - Rendimiento:
          Requisito: El sistema debe ser capaz de procesar las órdenes de dispensado de comida (tanto automáticas como manuales) en poco tiempo desde que se recibe la señal hasta que se activa el motor para                           liberar la comida.
          Contribución: Esto garantiza que el dispensador reaccione de manera rápida, mejorando la experiencia del usuario al evitar retrasos que podrían causar que la mascota espere demasiado o que el dueño                             piense que el sistema no está respondiendo.
     
      - Interfaz de Usuario:
          Requisito: El teclado matricial debe ser fácil de usar y permitir una configuración intuitiva de los horarios de dispensado y del modo de dispensado  manual.
          Contribución: Esto mejora la usabilidad del dispositivo, haciendo que los dueños de mascotas puedan configurar y usar el dispensador de manera sencilla sin necesidad de consultar un manual detallado.

-- Pruebas - Las pruebas seran realizadas simuladas por humanos

       - Prueba de Dispensado Automático
            - Objetivo: 
              Verificar que el sistema dispense la cantidad correcta de comida en los horarios configurados.
            - Procedimiento:
              Programar un horario específico para el dispensado de comida.
              Esperar a que se cumpla el tiempo.
              Medir la cantidad de comida dispensada y comparar con la cantidad programada.
            - Criterio de Éxito: 
              La cantidad de comida dispensada coincide con la cantidad configurada en el sistema.
     
       - Prueba de Dispensado Manual
            - Objetivo: 
              Verificar que el usuario pueda dispensar comida manualmente mediante el teclado matricial.
            - Procedimiento:
              Presionar la tecla designada en el teclado para el dispensado manual de comida.
              Medir la cantidad de comida liberada.
              Repetir la operación varias veces para asegurar consistencia.
            - Criterio de Éxito: 
              El sistema dispensa la comida inmediatamente después de recibir la instrucción manual, y la cantidad es la esperada.
     
       - Prueba de Detección de Niveles de Comida
            - Objetivo: 
              Comprobar que el sistema detecte correctamente los niveles de comida en el comedero y actúe en consecuencia.
            - Procedimiento:
              Vaciar el compartimento de almacenamiento.
              Llenar el compartimento hasta diferentes niveles.
              Verificar que el sistema registre correctamente cada nivel.
            - Criterio de Éxito: 
              El sistema detecta cada nivel de comida correctamente.
     
       - Prueba de Configuración del Teclado Matricial
            - Objetivo: 
              Asegurar que el usuario pueda configurar horarios y cantidades mediante el teclado matricial.
            - Procedimiento:
              Introducir un nuevo horario y una cantidad de comida.
              Verificar que la configuración se haya guardado correctamente.
            - Criterio de Éxito: 
              El sistema respeta los ajustes configurados a través del teclado matricial.
     
       - Prueba de Medidor de Nivel de Agua
            - Objetivo: 
              Asegurar que el sistema detecte el nivel de agua en el dispensador.
            - Procedimiento:
              Llenar el depósito de agua a diferentes niveles.
              Verificar que el sistema registre correctamente cada nivel.
              Vaciar el depósito y comprobar si se genera una alerta de nivel bajo de agua.
            - Criterio de Éxito: 
              El sistema detecta correctamente cada nivel de agua.

       - Prueba de Seguridad del Compartimento de Almacenamiento
            - Objetivo: 
              Verificar que el compartimento de almacenamiento de comida esté adecuadamente bloqueado y que solo pueda ser desbloqueado mediante la  secuencia correcta en el teclado matricial.
            - Procedimiento:
              Intentar abrir el compartimento sin introducir ninguna secuencia en el teclado.
              Confirmar que el compartimento permanece bloqueado.
              Introducir una secuencia incorrecta en el teclado y volver a intentar abrir el compartimento.
              Confirmar que el compartimento sigue bloqueado.
              Introducir la secuencia correcta (clave de desbloqueo configurada).
              Verificar que el compartimento se desbloquee correctamente.
              Después de un período predefinido, confirmar que el compartimento se bloquea automáticamente si no hay actividad.

      - Criterio de Éxito:
              El compartimento no se abre sin la secuencia correcta.
              Una secuencia incorrecta no permite el acceso al compartimento.
              La secuencia correcta desbloquea el compartimento.
              El compartimento se bloquea automáticamente después de un tiempo sin actividad.

 -- Las funciones de los integrantes del grupo son:
    
     -Duvan Camilo Ramirez Caro: Desarrollo del Software (Configuración y manejo de los tiempos de dispensado de alimentos, sistema de censado para monitorear el nivel de comida) y apoyo en la integración y                                     desarrollo del hardware del dispensador.
        
    -Juan Esteban Lopez Dominguez: Desarrollo del Software (implementación del sistema de seguridad, Modificación de la configuración de horarios para el dispensado de comida, ajuste de tiempos de dispensado                                   de alimentos, etc)
        
    -Jorge Andres Urrea Franco: Diseño y construcción de la estructura física del dispensador de alimentos, configuración de Hardware.

-- Circuitos Analogicos

        •	Sensar el nivel de comida en el comedero y en el almacenamiento
            1.	Usaremos un sensor de ultrasonido HC-SR04
            2.	Fuente de alimentación de 5V para el sensor
            3.	Conexión del trigger a la Raspberry Pi Pico
            4.	Divisor de voltaje en el pin echo para evitar dañar el pin
        •	Sensado del nivel de agua
            1.	Usaremos un sensor resistivo de nivel de agua que mide el nivel de líquido en función de la resistencia del agua entre sus conductores.
            2.	Fuente de alimentación de 5V para el sensor
            3.	Conexión de la señal de salida a la Raspberry Pi Pico: La salida del sensor proporciona una señal analógica de 0 a 5V, que representa el nivel del agua. Acá también debemos hacer un divisor de                     voltaje para no dañar el pin.
        •	Mecanismo de Liberación de Comida 
            1.	Utilizaremos un servomotor de giro completo para el mecanismo de dispensado
            2.	Conexión a la Raspberry Pi Pico: El servomotor se conecta a un pin PWM de la Raspberry Pi Pico
            3.	Fuente de alimentación para el servomotor
            4.	Control mediante señal PWM para activar el servomotor 
        •	Unidad de Activación Manual con un botón
            1.	Botón de activación manual
            2.	Conexión del botón a la Raspberry Pi Pico con una resistencia pull-up
        •	Sistema de Potencia 
            1.	Fuente de alimentación de 5V para motores y sensores
            2.	Control de potencia mediante transistores o MOSFETs
            3.	Filtro y estabilización con capacitores cerca de los motores y la fuente de alimentación

-- Hardware:

        Teclado Matricial:
            •	Permite al usuario ingresar configuraciones y órdenes.
            •	La señal lógica de entrada es leída por la Raspberry Pi Pico y utilizada para autenticación y configuración.
        Proceso de Autenticación y Seguridad:
            •	La Raspberry Pi Pico valida la entrada del teclado. Si la entrada es correcta se permite el acceso y se envía la señal de acción al bloque de decisón.
            •	Si la entrada es incorrecta, se activa un mecanismo de seguridad que muestra un error a través de un LED o mantiene el sistema bloqueado.
        Sensor de Nivel de Comida:
            •	Envía una señal lógica a la Raspberry Pi Pico que indica el nivel de comida actual.
            •	Esta señal se combina con la lógica de control para decidir si se debe activar el motor y ver cuanto alimento debe de dispensar.
        Decisión en Raspberry Pi Pico:
            •	Selecciona la acción a seguir basada en las señales de entrada del teclado y del sensor de nivel.
            •	Determina si se debe activar el motor para dispensar comida o si se mantiene el estado actual.
        Proceso de Control del Motor:
            •	Cuando se decida dispensar comida, la Raspberry Pi Pico envía una señal lógica al motor.
            •	Si no hay orden de acción, se mantiene el sistema sin cambios.
        Motor de Liberación de Comida:
            •   Ejecuta la acción de dispensar comida cuando recibe la señal de activación de la Raspberry Pi Pico.

-- Estructura del programa

        Inicialización
            1.	Configuración de periféricos y GPIOs:
                Se inicializan las variables globales y se configuran los pines GPIO para manejar el teclado matricial, el motor, y los sensores (como el nivel de comida). También se definen los pines para los                    LEDs indicadores.
            2.	Estado inicial:
                La máquina de estados comienza en el estado de espera, indicando que está listo para recibir entradas.
            3.	Interrupciones críticas:
                Se habilitan interrupciones para manejar eventos importantes:
                o	Lectura del teclado matricial para permitir acceso, por ejemplo.
        Flujo del sistema:
            1.	Estado de espera:
                o	En este estado, el sistema espera eventos desde el teclado.
                o	Si se detecta una pulsación en el teclado, el sistema pasa al estado de autenticación.
            2.	Autenticación (polling+interrupciones):
                o	La clave ingresada por el usuario se compara con la clave almacenada en el sistema.
                o	Si es incorrecta:
                    -Se activa el LED rojo para indicar un acceso denegado.
                    -El sistema regresa al estado de espera.
                o	Si es correcta:
                    -Se activa el LED verde para indicar un acceso concedido.
                    -El sistema pasa al estado de configuración.
            3.	Configuración y dispensado (polling+interrupciones):
                o	El usuario puede configurar parámetros como la cantidad de comida a dispensar.
                o	Antes de dispensar, se verifica si hay suficiente comida disponible.
                o	Si hay comida suficiente:
                    -Se activa el motor y se dispensa la cantidad deseada.
                o	Una vez finalizado el dispensado, el sistema regresa al estado de espera.
            4.	Estado final:
                o	Una vez finalizado el dispensado, el motor se apaga y el sistema regresa al estado de espera.

-- Manejo del repositorio

        Repositorio en GitHub:
        •	El repositorio es accesible por todos los miembros del equipo.
        Acceder directamente al repositorio en GitHub:
        •	Todos los miembros del equipo trabajan directamente en la rama principal. 
        Realizar cambios y confirmar (commit):
        •	Cada vez que un miembro realiza cambios, debe hacer un commit en GitHub para guardar esos cambios en el repositorio. 
        Sincronización entre miembros:
        •	Nos aseguraremos de coordinarnos para no sobrescribir el trabajo sin consentimiento de todos los miembros.





