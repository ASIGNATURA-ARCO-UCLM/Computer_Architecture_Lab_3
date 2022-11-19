# Tarea 4: Análisis de memoria y mejora vectorización
##### g++ -g -openmp complexmul.cpp -lm -o ejecutable -I ~/intel/oneapi/advisor/2022.3.0/include -lgomp -ldl
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
            Por lo que se puede observar, mayoritariamente tanto el bucle exterior (71%) como el interior (83%) poseen un stride uniforme o unitario (es decir, que las instrucciones acceden a una memoria que cambia de un elemento en un elemento con cada iteración); mientras que aparecen pocos strides no unitarios (29% y 17%, respectivamente). 
            Resulta deseable contar con un stride uniforme porque eso significaría que, sin importar en que iteración den un bucle nos encontremos, las instrucciones siempre accederán a las mismas posiciones de memoria. Esto evitará fallos de caché que deriven en retrasos debido a esperas a la jerarquía de memoria y permitirá una mejor planificación de recursos para los programas.


    * Busca el bucle más interno (el del índice j en el código original) y comprueba que el stride es de 2.
        * ¿Por qué el stride tiene este valor? (Revisa los conceptos de row-order y column-order así como el orden en el que se reserva la memoria en C)
            Debido a que en las dos instrucciones que se ejecutan durante una de sus iteraciones, se requiere la lectura de dos enteros, la parte imaginaria y real de un número complejo determinado (b[j][REAL] y b[j][IMAG]). Así, la memoria accedida por las instrucciones del bucle variará en "2*tamaño de un entero" bytes con cada iteración.

        * ¿Sobre que variables se está accediendo con un stride de 2? ¿Cómo afecta esto a la caché?
            Se accederá a la columna 0 y columna 1 de una misma fila determinda de la matriz b (será apuntada por la variable j en sí misma). Como se ha mencionado antes, con cada iteración, la caché necesitará recoger "2*tamaño de un entero" bytes, así que es fácil de suponer que cada vez que se realicen "Tamaño Caché/(2*Tamaño de un entero)" iteraciones, ésta fallará y deberá consultar a instancias superiores del subsistema de memoria.

        * ¿Se te ocurre algún modo de modificar el programa, manteniendo los dos bucles y el mismo resultado, para que
        el acceso a la variable sea uniforme? Realiza la modificación y almacena el resultado en esta misma carpeta con el nombre complexmul_unit_stride.cpp.


        
* Genera un snapshot para el análisis completo (hasta los patrones de acceso a memoria) tanto para la versión con un stride de 2 como para la versión con stride unitario (ambos vectorizando el código) y llámalos respectivamente "task4a" y "task4b", añádelos a esta misma carpeta. 
    * En "task4b" ¿Cuáles son los valores de la longitud del vector y la ganancia estimada? ¿Son los resultados que se esperaban? Justifica la respuesta.
    * Comparando estas dos soluciones ¿Cuánto ha aumentado la ganancia?

* Compara los resultados del análisis task2 y task4b:
    * ¿Cuál ha sido la ganancia real del algoritmo vectorizado? ¿Ha sido menor o mayor a la estimación?