# Tarea 4: Análisis de memoria y mejora vectorización

## Preguntas

* Compila de nuevo el programa complexmul.cpp **sin vectorizar** y genera un análisis de memoria marcando los bucles del cómputo que realizan la mutliplicación de números complejos, en concreto marca los bucles de las líneas 27 y 28 (si el análisis se demora mucho prueba a reducir el tamaño). Realiza el análisis tanto usando la interfaz gráfica de intel advisor como por línea de comandos. Además indica que comando es el que has usado para realizar el análisis por comando.

**PARA LA REALIZACIÓN DE ESTA TAREA SE HA REDUCIDO EL TAMAÑO DE LAS FILAS DE LAS MATRICES A 500**

* Abre advisor y selecciona la vista "Refinement Reports".
    * ¿Qué información nos proporciona esta vista? enumera cada elemento de la tabla resumiendo el significado
    
            - **Loop-Carried Dependencies**: Resume la presencia de dependecia a lo largo de una iteración de un determinado bucle (tanto RAW, WAW como WAR)
            - **Strides Distribution**: Aclara el porcentaje de strides unitarios, constantes y variables en el código seleccionado
            - **Access Pattern**: Aporta información acerca de los tipos de Stride encontrados en el código seleccionado
            - **Max. Per-Instruction Addr. Range**: Distancia máxima entre la mínima y máxima posición de memoria que son accedidas en el bucle (a través de todas sus iteraciones)
            - **First Instance Site Footprint**: Bytes de memoria principal ocupados por la ejecución de la primera iteración del bucle
            - **Simulated Memory Footprint**: Los bytes SIMULADOS de memoria principal ocupados por la ejecución de la primera iteración del bucle (Líneas de caché usadas * Tamaño línea de caché)
            - **Site Name**: Nombre dado en la anotación del código al bloque tratado.
            - **Performance Issues**: Recomendaciones relacionadas con análisis más profundos.
            - **Cache Line Utilization**: Utilización simulada de líneas de cache para operaciones de transferencia de datos
            - **Memory Loads**: Número de operaciones "load" ocurridas durante la primera iteración del bucle seleccionado
            - **Memory Stores**:Número de operaciones "store" ocurridas durante la primera iteración del bucle seleccionado
            - **Cache Misses**: Número de operaciones "load" realizadas por subsistemas de memoria superiores a la caché ocurridas durante la primera iteración del bucle seleccionado
            - **RFO Cache Misses**: Número de líneas de caché cargadas debido a una solicitud de modificación de datos
            - **Dirty Evictions**: Número de líneas de caché desalojadas con un estado modificado que genera tráfico de memoria ascendente a un subsistema de memoria superior
            

    * ¿Qué comportamiento de memoria se obtiene con el código original? ¿Por qué es deseable tener un stride uniforme?
    
            Por lo que se puede observar, mayoritariamente tanto el bucle exterior (71%) como el interior (83%) poseen un 
            stride uniforme o unitario (es decir, que las instrucciones acceden a una memoria que cambia de un elemento en
            un elemento con cada iteración); mientras que aparecen pocos strides no unitarios (29% y 17%, respectivamente). 
            Resulta deseable contar con un stride uniforme porque eso significaría que, sin importar en que iteración den un
            bucle nos encontremos, las instrucciones siempre accederán a las mismas posiciones de memoria. Esto evitará fallos
            de caché que deriven en retrasos debido a esperas a la jerarquía de memoria y permitirá una mejor planificación de
            recursos para los programas.


    * Busca el bucle más interno (el del índice j en el código original) y comprueba que el stride es de 2.
        * ¿Por qué el stride tiene este valor? (Revisa los conceptos de row-order y column-order así como el orden en el que se reserva la memoria en C)
        
            Debido a que C reserva el espacio en memoria para las diferentes posiciones de la matriz porcolumnas en lugar de por filas, que suele ser lo esperable. Así, a la hora de realizar las operaciones con los números complejos, como se necesita la componente real y la imaginaria, si ambas están dispuestas en la misma fila y diferente columna, la caché primero cargará un conjunto de datos referidos a la columna de la parte real, requiriendo otra lectura de un conjunto de datos que contengan la información de la parte imaginaria (situada en la otra columna). 

        * ¿Sobre que variables se está accediendo con un stride de 2? ¿Cómo afecta esto a la caché?

            Lo que ocurre en este programa es que al realizar una lectura por parte de la caché, ésta obtendrá el contenido de ciertas posiciones de la primera columna de la matriz en cuestión. Esto supondrá la carga de las partes reales de algunos números complejos, pero eso es en realidad contraproducente ya que no se tendrán datos de ninguna componente imaginaria. Así, cuando estas últimas se necesiten, irremediablemente ocurrirá un fallo de caché.

            Si esto se solucionase llegando a un stride unitario, con una simple lectura de caché se obtendrían datos de los dos componentes de una cantidad determinada de números complejos (se extraerían los valores de una columna, que sólo contará con dos elementos y representa a un complejo, y la memoria pasará a leer la siguientes columnas).

        * ¿Se te ocurre algún modo de modificar el programa, manteniendo los dos bucles y el mismo resultado, para que
        el acceso a la variable sea uniforme? Realiza la modificación y almacena el resultado en esta misma carpeta con el nombre complexmul_unit_stride.cpp.
        
               Esto se consigue modificando la organización de los datos referidos a la parte real e imaginaria de los números complejos a usar en las matrices de las que inicialmente se disponía: en lugar de que éstas posean dos columnas y N filas (tantas como números a emplear), pasen a tener N columnas y únicamente 2 filas. De esta manera, cuando se necesite acceder a ambos componentes de un número en una instrucción, la caché no fallará y se evitarán lecturas extra.


        
* Genera un snapshot para el análisis completo (hasta los patrones de acceso a memoria) tanto para la versión con un stride de 2 como para la versión con stride unitario (ambos vectorizando el código) y llámalos respectivamente "task4a" y "task4b", añádelos a esta misma carpeta. 
    * En "task4b" ¿Cuáles son los valores de la longitud del vector y la ganancia estimada? ¿Son los resultados que se esperaban? Justifica la respuesta.
    
            La longitud del vector es igual a 8 y la ganancia es 7,66. Quizá sería esperable una ganacia superior a 8 por el valor de vector length obtenido (si puedes hacer 8 operaciones con elementos de vectores a la vez, tu programa será 8 veces más rápido que uno escalar), pero está dentro de lo razonable.

    * Comparando estas dos soluciones ¿Cuánto ha aumentado la ganancia?
            En el caso de la "task4a", la ganancia es de 7,07 (y el vector length 16), por lo que se puede asegurar que con la simple mejora de los strides del programa, se hace posible que éste se ejecute de manera mucho más rápida. En concreto y en este caso, la versión de stride unitario es 1.0834 veces más veloz, resultando asíi sus tiempos consumidos:
            * task4b --> 0.37
            * task4a --> 0.61

* Compara los resultados del análisis task2 y task4b:
    * ¿Cuál ha sido la ganancia real del algoritmo vectorizado? ¿Ha sido menor o mayor a la estimación?
            El tiempo requerido por el programa de "task2" fue de 17,75 segundos aproximadamente. Como en la "task4b" es de 0.37, a pesar de tenerse como speedup esperado 7,66, éste resulta 47,97 a partir de la división del primer valor entre el segundo. 
            El programa que hemos conseguido supera la estimación inicial.
