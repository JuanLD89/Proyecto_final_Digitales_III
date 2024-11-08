# Proyecto_final_Digitales_III
Proyecto de un dispensador de comida inteligente para mascotas con Raspberry Pi Pico. Automatiza la alimentación mediante horarios programables y detección de niveles de comida y agua. Incluye opciones de dispensado manual y teclado para configuración.

-- Nombre del proyecto. 
    - Happy pet!!

-- Idea de proyecto final 
    - El proyecto consiste en la creación de un dispensador de comida inteligente para mascotas, utilizando la Raspberry Pi Pico como unidad de control principal.       Este dispositivo tiene como objetivo proporcionar una solución automatizada para la alimentación de mascotas, permitiendo que reciban su comida de manera          regular y en cantidades controladas, incluso cuando los dueños no están presentes.
    - Una característica clave del dispensador es su capacidad para detectar los niveles de comida restantes en el compartimento de almacenamiento. Si se detecta        que el nivel es bajo y coincide con el horario programado para la alimentación, el dispositivo liberará la cantidad necesaria de comida para evitar que se         derrame. De esta manera, se garantiza que la comida se distribuya de manera precisa y controlada, manteniendo el área de alimentación limpia y organizada.
    - También se pondrá un teclado matricial que controle el bloqueo al compartimento de almacenamiento, configuración de hora de dispensado y de proporciones.

-- Requisitos funcionales.
    - Automatización de la Alimentación:
      - El sistema permitirá la programación de horarios para la dispensación de comida mediante el teclado matricial.
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
          El usuario puede dispensar manualmente la comida, independientemente de la programación automática de horarios. Esto le permitirá al usuario proporcionar          comida adicional a la mascota en caso de ser necesario.

-- Requisitos NO funcionales.
      - Rendimiento:
          Requisito: El sistema debe ser capaz de procesar las órdenes de dispensado de comida (tanto automáticas como manuales) en poco tiempo desde que se recibe la señal hasta que se activa el                                      motor para liberar la comida.
          Contribución: Esto garantiza que el dispensador reaccione de manera rápida, mejorando la experiencia del usuario al evitar retrasos que podrían causar que la mascota espere demasiado o que                                      el dueño piense que el sistema no está respondiendo.
      - Fiabilidad:
          Requisito: El dispensador debe tener una tasa de error baja en la detección de niveles de comida y agua, para asegurar que siempre detecte adecuadamente cuando es necesario rellenar el                                       depósito.
          Contribución: Asegura que el sistema proporcione información precisa sobre la cantidad de comida y agua disponible, evitando posibles situaciones en las que la mascota quede sin alimentación                                    por fallos en la detección.
      - Interfaz de Usuario:
          Requisito: El teclado matricial debe ser fácil de usar y permitir una configuración intuitiva de los horarios de dispensado y del modo de dispensado manual.
          Contribución: Esto mejora la usabilidad del dispositivo, haciendo que los dueños de mascotas puedan configurar y usar el dispensador de manera sencilla sin necesidad de consultar un                                             manual detallado.
      - Disponibilidad:
          Requisito: El sistema deberá ser capaz de funcionar de manera continua, con un tiempo bajo de inactividad.
          Contribución: Asegura que el dispensador esté disponible para dispensar comida en todo momento, especialmente en horarios críticos, como cuando los dueños no están en casa.
      - Escalabilidad:
          Requisito: El sistema deberá permitir la adición de nuevos sensores o funcionalidades sin necesidad de modificar el diseño de hardware existente.
          Contribución: Esto facilita futuras mejoras al sistema, como la integración de sensores de temperatura o humedad, haciéndolo más adaptable a nuevas necesidades del usuario.

-- Pruebas. 
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

