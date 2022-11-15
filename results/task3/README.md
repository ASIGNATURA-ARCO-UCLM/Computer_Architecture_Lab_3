# Tarea 3: Vectorización

## Preguntas
* Antes de comenzar la vectorización es importante conocer cuáles son las características de tu máquina ¿Cuáles son las extensions multimedia SIMD con las que cuenta tu arquitectura?

      Buscando el procesador en la página oficial de Intel obtenemos toda la información acerca de éste. Si pinchamos en 
      'Tecnologías avanzadas' y buscamos 'Extensiones de conjunto de instrucciones' obtenemos las extensiones.
      En nuestro caso son las siguientes:  Intel® SSE4.1, Intel® SSE4.2, Intel® AVX2

* Observa el análisis que has realizado al programa complexmul.cpp. El propio Intel Advisor debe haber detectado que hay una infrautilización de instrucciones, esto está directamente relacionado con la vectorización, ya que lo que pretende reflejar es que tienes disponibles las extensiones SIMD y no las estás utilizando. Para vectorizar el algoritmo, el propio programa Intel Advisor te aconseja como hacerlo ¿Qué has hecho para vectorizar el bucle? Ten en cuenta que debes vectorizar lo máximo que te permita tu arquitectura.

* Una vez vectorizado el programa realiza un análisis y guárdalo con el nombre task3:
    * ¿Cual es el valor del campo Vector Length? ¿Es este el valor esperado? Tanto si la respuesta es afirmativa como negativa justifica cual es el valor que esperabas.
    * ¿Cuál ha sido la ganancia? Explica si es el resultado esperado, si no lo es, explica cuál crees que es la razón (Pista: Intel Advisor puede darte indicios de cuál es el problema).


