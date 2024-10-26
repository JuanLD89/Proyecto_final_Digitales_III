# Proyecto_final_Digitales_III
Proyecto de un dispensador de comida inteligente para mascotas con Raspberry Pi Pico. Automatiza la alimentación mediante horarios programables y detección de niveles de comida y agua. Incluye opciones de dispensado manual y teclado para configuración.

- El proyecto final del curso de Electrónica Digital III consiste en desarrollar una aplicación o sistema embebido que utilice el MCU del curso y que involucre el uso de sensores, actuadores, Interfaz Humano Máquina, módulos de comunicación, etc. Los estudiantes deberán conformar grupos de trabajo para la realización del proyecto. Si bien no se establece un máximo de estudiantes, la complejidad del proyecto y el número de integrantes del grupo debe ser coherente. Cada grupo definirá los requisitos y características de la aplicación o sistema que diseñará. Este cuestionario recoge información básica necesaria para comprender la propuesta de trabajo que cada grupo quiere realizar.

- Esta segunda ronda de información busca mejorar la definición del proyecto e incluir la realimentación que el profesor realizo en la primera ronda.

- Ten en cuenta estas recomendaciones para responder las preguntas:

- Nombre del proyecto: 
El nombre debe ser corto como el de un producto comercial y no el titulo de un proyecto.

- Descripción del proyecto: 
Describe de la mejor forma posible la idea de proyecto final. Acompaña tu idea con diagramas de bloque que ayuden al profesor a comprender mejor lo que quieres hacer. 

- Requisitos funcionales: 
En el contexto de sistemas embebidos, los requisitos funcionales se refieren a las especificaciones detalladas de las funciones y el comportamiento que un sistema embebido debe cumplir para satisfacer sus objetivos y requerimientos. Estos requisitos describen las acciones y operaciones específicas que el sistema debe realizar en respuesta a estímulos o entradas particulares. Los requisitos funcionales son esenciales para definir cómo un sistema embebido debe interactuar con su entorno y proporcionar las capacidades necesarias.

Algunos ejemplos de requisitos funcionales en sistemas embebidos podrían incluir:

1. Procesamiento de datos: Especificaciones sobre cómo el sistema embebido debe procesar los datos de entrada, como la velocidad de procesamiento, los algoritmos a utilizar y los resultados esperados.

2. Comunicación: Requisitos que definen cómo el sistema debe comunicarse con otros dispositivos o sistemas, incluyendo protocolos de comunicación, tasas de transferencia de datos y latencia.

3. Control: Descripciones detalladas de cómo el sistema debe controlar dispositivos o actuadores, como motores, sensores o pantallas, incluyendo los valores de referencia, los umbrales y las respuestas esperadas.

4. Gestión de energía: Especificaciones sobre cómo el sistema debe administrar el consumo de energía, como el modo de ahorro de energía, la gestión de baterías y la duración de la energía.

5. Interfaz de usuario: Requisitos que describen la interacción del usuario con el sistema, incluyendo la apariencia de la interfaz, las acciones disponibles y las respuestas del sistema a las entradas del usuario.

6. Seguridad: Especificaciones relacionadas con medidas de seguridad y protección de datos, como autenticación, cifrado y gestión de amenazas.

7. Tiempos de respuesta: Requisitos que establecen los límites de tiempo dentro de los cuales el sistema debe responder a eventos o entradas específicas.

8. Cumplimiento de estándares: Especificaciones que indican qué estándares o normativas debe cumplir el sistema embebido, como regulaciones de seguridad, estándares de comunicación, etc.

Estos son solo algunos ejemplos de requisitos funcionales en sistemas embebidos, y pueden variar significativamente según la aplicación y el contexto específico del sistema en cuestión. La definición precisa de estos requisitos es fundamental para el diseño, desarrollo y verificación exitosos de sistemas embebidos.

- La redacción de requisitos funcionales en sistemas embebidos es una parte crucial del proceso de desarrollo, ya que establece la base para el diseño y la implementación. Aquí hay algunas recomendaciones para la redacción efectiva de requisitos funcionales en sistemas embebidos:

1. Sé claro y conciso: Los requisitos deben ser redactados de manera clara y concisa. Utiliza un lenguaje simple y evita la ambigüedad. Deben ser comprensibles tanto para los desarrolladores como para los usuarios finales.

2. Usa verbos de acción: Utiliza verbos de acción como "debe", "deberá", "debería" para indicar las acciones que el sistema debe realizar. Esto ayuda a clarificar las expectativas y las responsabilidades del sistema.

3. Especifica condiciones y criterios de aceptación: Además de describir lo que el sistema debe hacer, incluye condiciones claras para determinar cuándo se considera que un requisito se ha cumplido. Esto facilita la verificación y validación posterior.

4. Evita requisitos redundantes: Asegúrate de que cada requisito sea único y no se duplique en otros lugares de la documentación. La redundancia puede llevar a la confusión y a problemas de mantenimiento.

5. Mantén la trazabilidad: Asocia cada requisito con el objetivo o la necesidad que está destinado a abordar. Esto facilita la trazabilidad y ayuda a garantizar que cada requisito sea realmente necesario.

5. Prioriza los requisitos: Establece una jerarquía de prioridades para los requisitos. Esto ayuda a los equipos de desarrollo a centrarse en los aspectos más críticos del sistema cuando se enfrentan a restricciones de tiempo o recursos.

Escribe de forma detallada todas las funcionalidades de tu proyecto. Estas se usaran para verificar en la entrega final si cumpliste o no con lo planteado aquí.

- Requisitos NO funcionales: 
En el contexto de sistemas embebidos, los requisitos NO funcionales se refieren a los aspectos y características del sistema que no están relacionados directamente con las funciones específicas que debe realizar, sino que se centran en cómo el sistema debe operar, su rendimiento, seguridad, escalabilidad y otros atributos de calidad. Estos requisitos son igualmente importantes que los requisitos funcionales, ya que afectan la experiencia del usuario y la capacidad del sistema para cumplir con sus objetivos. Aquí tienes algunos ejemplos de requisitos no funcionales en sistemas embebidos:

1. Rendimiento: Establece la velocidad, la eficiencia y la capacidad de respuesta del sistema. Ejemplo: "El sistema embebido debe ser capaz de procesar un mínimo de 1000 transacciones por segundo".

2. Disponibilidad: Define el tiempo durante el cual el sistema debe estar en funcionamiento y accesible. Ejemplo: "El sistema debe tener una disponibilidad del 99.9% durante las horas hábiles".

3. Seguridad: Especifica las medidas de seguridad que deben implementarse para proteger los datos y el sistema en sí. Ejemplo: "El sistema debe cumplir con los estándares de seguridad ISO 27001".

4. Fiabilidad: Indica la capacidad del sistema para funcionar de manera consistente y sin fallos. Ejemplo: "El sistema no debe fallar más de una vez al mes".

5. Escalabilidad: Describe la capacidad del sistema para crecer y adaptarse a cambios en la carga de trabajo. Ejemplo: "El sistema debe ser escalable para admitir hasta 1000 usuarios concurrentes".

6. Mantenibilidad: Define cómo se debe mantener y actualizar el sistema con el tiempo. Ejemplo: "El sistema debe permitir actualizaciones de software sin tiempo de inactividad".

7. Interoperabilidad: Especifica cómo el sistema debe interactuar con otros sistemas o dispositivos. Ejemplo: "El sistema debe ser compatible con los protocolos de comunicación estándar de la industria".

8. Usabilidad: Describe la facilidad de uso del sistema y la experiencia del usuario. Ejemplo: "La interfaz de usuario debe ser intuitiva y requerir una capacitación mínima para los usuarios".

9. Consumo de energía: Indica los requisitos de eficiencia energética del sistema. Ejemplo: "El sistema debe operar con un consumo de energía no superior a 5 vatios".

10. Cumplimiento normativo: Establece los estándares y regulaciones específicos que el sistema debe cumplir. Ejemplo: "El sistema debe cumplir con las regulaciones de seguridad de la FDA para dispositivos médicos".

11. Tiempos de respuesta: Define el tiempo máximo permitido para que el sistema responda a eventos específicos. Ejemplo: "El sistema debe proporcionar una respuesta en menos de 100 milisegundos a las solicitudes de usuario".

12. Tolerancia a fallos: Describe cómo el sistema debe manejar situaciones de fallo sin interrupciones graves. Ejemplo: "El sistema debe ser capaz de recuperarse automáticamente de fallos de hardware sin pérdida de datos".

Estos son solo ejemplos de requisitos no funcionales en sistemas embebidos, y la lista puede variar según las necesidades específicas del proyecto y la aplicación. Estos requisitos son fundamentales para garantizar que el sistema embebido cumpla con los estándares de calidad y rendimiento deseados. ATENCIÓN: los requisitos NO funcionales son más dificiles de cumplir, solo comprometase con aquellos requisitos que estas 100% seguro que sabes como cumplir y que realmente piensas hacerlo. Si no te comprometes con requisitos no funcionales no es un problema.

- Escenario de pruebas:
La idea de esta pregunta es que me cuentes como vas a probar la funcionalidad de tu proyecto el día de la entrega. Para de esta forma determinar si es posible evaluar la funcionalidad completa descrita en este cuestionario. No dejes nada al azar, pensa en cada detalle. Puedes incluir diagramas y bocetos de como sería el escenario de pruebas.

- Presupuesto:
El análisis de costos iniciales de un producto o sistema electrónico es un paso fundamental para evaluar la viabilidad económica de un proyecto. Aquí tienes una guía para abordar este análisis:

1. Identifica los componentes principales: Enumera todos los componentes principales del producto o sistema electrónico, como hardware, software, sensores, circuitos integrados, placas de circuito impreso, pantallas, baterías, etc.

2. Costo de los componentes: Determina el costo de cada uno de los componentes identificados. Esto puede requerir investigar proveedores, cotizar precios y considerar la compra a granel para obtener descuentos.

3. Herramientas y equipos: Considera los costos de las herramientas y equipos necesarios para el desarrollo, como equipos de prueba, estaciones de trabajo, herramientas de diseño y software de desarrollo.

4. Costos de diseño y prototipado: Ten en cuenta los costos relacionados con el diseño del producto, la creación de prototipos y la validación de conceptos. Esto puede incluir diseño de PCB, diseño de carcasas, impresión 3D, pruebas y ensayos.

El análisis de costos iniciales es esencial para determinar si un producto o sistema electrónico es viable desde el punto de vista económico. Ayuda a tomar decisiones informadas sobre la inversión en el proyecto y proporciona una base sólida para la planificación financiera y la gestión del proyecto.

- Repositorio:
El repositorio debe usarse a lo largo del desarrollo del proyecto y no solo un día antes de la entrega del proyecto final. Estructure el repositorio con ramas de desarrollo que reflejen la division del trabajo entre los compañeros. Documente el repositorio con las respuestas de este cuestionario: nombre del proyecto, descripción y diagramas de bloque, listas de requisitos funcionales y no funcionales, y el presupuesto.

Cuestionario:

-- Por favor ingrese un nombre para su proyecto. Utiliza un nombre llamativo para tu proyecto,  idealmente un texto corto como el de un producto comerciales.
Texto de la respuesta Pregunta 1

    - Happy pet!!

-- Describa detalladamente su idea de proyecto final y dibuje un diagrama de bloques del sistema. Puedes decribir el proyecto aquí o adjuntar un archivo pdf con la descripción y el diagrama de bloques. Recuerda que un diagrama de bloques es muy diferente de un diagrama de flujo.

    - El proyecto consiste en la creación de un dispensador de comida inteligente para mascotas, utilizando la Raspberry Pi Pico como unidad de control principal.       Este dispositivo tiene como objetivo proporcionar una solución automatizada para la alimentación de mascotas, permitiendo que reciban su comida de manera          regular y en cantidades controladas, incluso cuando los dueños no están presentes.
  
      Una característica clave del dispensador es su capacidad para detectar los niveles de comida restantes en el compartimento de almacenamiento. Si se detecta        que el nivel es bajo y coincide con el horario programado para la alimentación, el dispositivo liberará la cantidad necesaria de comida para evitar que se         derrame. De esta manera, se garantiza que la comida se distribuya de manera precisa y controlada, manteniendo el área de alimentación limpia y organizada.
  
      También se pondrá un teclado matricial que controle el bloqueo al compartimento de almacenamiento, configuración de hora de dispensado y de proporciones.

-- Haga una lista de todos los requisitos funcionales con los que deberá cumplir su proyecto en la entrega final.

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

-- Haga una lista de todos los requisitos NO funcionales con los que deberá contar su proyecto en la entrega final. Describa como cada uno de ellos contribuye a mejorar la calidad del producto.

      - Rendimiento:
          Requisito: El sistema debe ser capaz de procesar las órdenes de dispensado de comida (tanto automáticas como manuales) en poco tiempo desde que se                 recibe la señal hasta que se activa el motor para liberar la comida.
          Contribución: Esto garantiza que el dispensador reaccione de manera rápida, mejorando la experiencia del usuario al evitar retrasos que podrían causar              que la mascota espere demasiado o que el dueño piense que el sistema no está respondiendo.
      
      - Fiabilidad:
          Requisito: El dispensador debe tener una tasa de error baja en la detección de niveles de comida y agua, para asegurar que siempre detecte adecuadamente           cuando es necesario rellenar el depósito.
          Contribución: Asegura que el sistema proporcione información precisa sobre la cantidad de comida y agua disponible, evitando posibles situaciones en las           que la mascota quede sin alimentación por fallos en la detección.
          
      - Interfaz de Usuario:
          Requisito: El teclado matricial debe ser fácil de usar y permitir una configuración intuitiva de los horarios de dispensado y del modo de dispensado               manual.
          Contribución: Esto mejora la usabilidad del dispositivo, haciendo que los dueños de mascotas puedan configurar y usar el dispensador de manera sencilla            sin necesidad de consultar un manual detallado.
      
      - Disponibilidad:
          Requisito: El sistema deberá ser capaz de funcionar de manera continua, con un tiempo bajo de inactividad.
          Contribución: Asegura que el dispensador esté disponible para dispensar comida en todo momento, especialmente en horarios críticos, como cuando los                dueños no están en casa.
      
       -Escalabilidad:
          Requisito: El sistema deberá permitir la adición de nuevos sensores o funcionalidades sin necesidad de modificar el diseño de hardware existente.
          Contribución: Esto facilita futuras mejoras al sistema, como la integración de sensores de temperatura o humedad, haciéndolo más adaptable a nuevas                necesidades del usuario.

-- Describa detalladamente el escenario de pruebas necesario para demostrar todas las características de su proyecto final. El escenario puede incluir maquetas, espacios de ejecución para robots, sujetos de prueba, etc. 

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
              Verificar que el compartimento de almacenamiento de comida esté adecuadamente bloqueado y que solo pueda ser desbloqueado mediante la                              secuencia correcta en el teclado matricial.
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

