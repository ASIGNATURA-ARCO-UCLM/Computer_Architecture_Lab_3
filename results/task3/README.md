# Tarea 3: Vectorización

## Preguntas
* Antes de comenzar la vectorización es importante conocer cuáles son las características de tu máquina ¿Cuáles son las extensions multimedia SIMD con las que cuenta tu arquitectura?

      Buscando el procesador en la página oficial de Intel obtenemos toda la información acerca de éste. Si pinchamos en 
      'Tecnologías avanzadas' y buscamos 'Extensiones de conjunto de instrucciones' obtenemos las extensiones.
      En nuestro caso son las siguientes:  Intel® SSE4.1, Intel® SSE4.2, Intel® AVX2

* Observa el análisis que has realizado al programa complexmul.cpp. El propio Intel Advisor debe haber detectado que hay una infrautilización de instrucciones, esto está directamente relacionado con la vectorización, ya que lo que pretende reflejar es que tienes disponibles las extensiones SIMD y no las estás utilizando. Para vectorizar el algoritmo, el propio programa Intel Advisor te aconseja como hacerlo ¿Qué has hecho para vectorizar el bucle? Ten en cuenta que debes vectorizar lo máximo que te permita tu arquitectura.

      Así es, si pinchamos en 'Recomendaciones' vemos que disponemos de la extensión AVX2 pero no estamos haciendo uso de
      ella.
      Si hacemos caso a lo que nos dice y volvemos a compilar el archivo pero ahora añadiendo la opción de compilación
      '-xCORE-AVX2', que se usa para aquellas máquinas que tienen soporte para AVX2, pasamos de un Total time de casi
      21 segundos a uno de 0,640 segundos.
      También hemos hecho un análisis sobre el acceso a memoria en el propio Advisor obteniendo como resultado que las 
      instrucciones tenían un acceso a memoria irregular, entonces nos hemos puesto a modificar el código y ha resultado
      esto:
      
      int main() {
          float aReal[SIZE];
          float aImag[SIZE];
          float bReal[SIZE];
          float bImag[SIZE];
          auto c = new float[SIZE][2];
          double n = SIZE;
          double seed = 3.141592653589793;

          // Generate pseudo random numbers
          for(int i = 0; i < SIZE; i++) {
              aReal[i] = sin((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
              aImag[i] = cos((seed*i * (seed*i + 1) * (2 * seed*i + 1)) / 6);
              bReal[i] = sin((6*seed*i * ( seed*i - 1) + 1));
              bImag[i] = cos((6*seed*i * ( seed*i - 1) + 1));
          }

          double t = omp_get_wtime();

          for(int i = 0; i < SIZE; i++) {
              for(int j = 0; j < SIZE; j++) {
                  c[i][REAL] += (aReal[i] * bReal[j]) - (aImag[i] * bImag[j]);
                  c[i][IMAG] += (aReal[i] * bReal[j]) + (aReal[i] * bImag[j]);
              }
          }

          t = omp_get_wtime() - t;

          printf("Time elapsed to execute program: %.2f seconds\n", t);
      }
      
      Lo que hemos modificado es que en vez usar matrices para a y b hemos usado un vector para guardar los reales e
      imaginarios de cada uno. De esta forma en vez de acceder de arriba hacia abajo hace un acceso hacia la derecha.
      
      El resultado de hacer esto es que el Total time ha disminuido a 0.40 segundos aproximadamente.

* Una vez vectorizado el programa realiza un análisis y guárdalo con el nombre task3:
    * ¿Cual es el valor del campo Vector Length? ¿Es este el valor esperado? Tanto si la respuesta es afirmativa como negativa justifica cual es el valor que esperabas.
      
            El campo Vector Length es igual a 8

    * ¿Cuál ha sido la ganancia? Explica si es el resultado esperado, si no lo es, explica cuál crees que es la razón (Pista: Intel Advisor puede darte indicios de cuál es el problema).
            
            Hemos conseguido una ganancia de 8,37 consiguiendo un 100% de la eficiencia


