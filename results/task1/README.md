# Tarea 1: Intel Advisor

## Preguntas
* En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?

      Self time: Tiempo de ejecución activa de una función o bucle, sin incluir el tiempo de las funciones llamadas que dicho bucle o función pueda generar
      
      Total time: Tiempo de ejecución activa de una función o bucle junto con el de sus todos los subprocesos invocados 
      
      Mirando los resultados obtenemos que en los for anidados de las líneas 27 y 28 se va casi todo el tiempo total 
      (20,970 de 20,980) 
     

* Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará
más tarde).

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task1/capturaEj2.png)


* Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?

      El programa nos da muchas pistas sobre que está pasando, dice lo siguiente "roofline report depends on the
      floating-point and integer operations data, which is unavailable"
      
      Esto ocurre porque para hacer un gráfico roofline necesitamos los GFLOPS y la Intensidad Aritmética, que necesitan ser calculadas mediante los FLOPS (operaciones de punto flotante por segundo); pero como tenemos desmarcada esa opción el Advisor no conoce ese dato (y por eso nos dice que marquemos esa opción para resolver el problema).

* Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta
los datos nuevos más relevantes.

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task1/tarea1Ejer4.png)

      Tras hacer el análisis los nuevos datos más relevantes son:
      * Los GFLOPS (Total GFLOP / Total Elapsed Time) --> 1.128 GFLOPS para todo el programa (0.150 para el bucle en el que se rellenan las matrices con aleatorios y también 1.128 para los dos bucles de las lineas 27 y 28 que realizan la multiplicación de ellas) 
      * La Intensidad Aritmética (Ratio of Total Floating-Point Operations To Local L1 Trasnferred Bytes) --> 0.39 (en el bucle de relleno de matrices es de 0.103 y en el resto de bucles también 0.39)
      * Datos relacionados con el uso de memoria --> 28.775 GB/s transferidos entre la CPU y el subsistema de memoria   (1.460 para el bucle de relleno de matrices y 28.771 para el resto de bucles)
      * Llamadas a cada método y bucle --> El main() es llamado 1 sóla vez | El bucle de rellenado de matrices se invoca sólo 1 vez y se ejecuta 50.000 veces | El bucle de la línea 27 se invoca 1 sóla vez y se ejecuta 50.000 veces | El bucle de la línea 28 se invoca 50.000 veces y se ejecuta 50.000 veces por llamada.
