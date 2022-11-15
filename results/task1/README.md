# Tarea 1: Intel Advisor

## Preguntas
* En la vista de "Survey & Roofline" se hace referencia a Total time y self-time. ¿Qué diferencia hay entre ambas?

      Self time: es el tiempo que se emplea en una zona de código concreta
      
      Total time: es el tiempo que se emplea en correr todo el programa
      
      Mirando los resultados obtenemos que en los for anidados de las líneas 27 y 28 se va casi todo el tiempo total 
      (20,970 de 20,980) 
     

* Realiza un análisis de tipo Survey, accede a  la pestaña "Survey & Roofline" y haz una captura de la información (se usará
más tarde).

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task1/capturaEj2.png)


* Pulsa sobre roofline (dentro de Survey & Roofline) y comprueba que no aparece ningún gráfico. ¿A qué se debe?

      El programa nos da muchas pistas sobre que está pasando, dice lo siguiente "roofline report depends on the
      floating-point and integer operations data, which is unavailable"
      
      Y es que para hacer un gráfico roofline necesitamos los GFLOPS y la Intensidad Aritmética, para calcular ambas
      cosas necesitamos los FLOPS (operaciones de punto flotante por segundo) y como tenemos desmarcada esa opción en
      el Advisor no conoce ese dato, y por eso nos dice que marquemos esa opción para resolver el problema.

* Haz un análisis de trip-counts y flop. ¿Qué información nueva aparece en la vista de survey? Haz una captura y comenta
los datos nuevos más relevantes.

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task1/capturaEj4.png)

      Tras hacer el análisis los nuevos datos más relevantes son los GFLOPS, la Intensidad Aritmética y 
      también aparecen datos relacionados con el uso de memoria y ancho de banda
