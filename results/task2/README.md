# Tarea 2: Roofline
## Preguntas
1. Genera un roofline y analiza la información representada. Copia una captura del roofline en la respuesta
para apoyar tu análisis. Finalmente genera un snapshot con el nombre "task2" y añádelo a esta misma carpeta.

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task2/tarea2Ejer1.png)

2. ¿Por qué está limitado el algoritmo? ¿Qué técnicas podríamos aplicar para mejorar el rendimiento?
A la hora de analizar el gráfico obtenido, la propia herramienta Advisor nos comenta nuestro algoritmo está **limitado mayoritariamente por el ancho de banda de la memoria y en menor medida también  por la intensidad aritmética**.

También, nos ofrece una serie de recomendaciones para solucionar lo comentado arriba, como lo es la vectorización de los bucles (son escalares actualmente) o la mejora de la memoria DRAM y cachés compartidas, que empeoran el rendimimento de ejecución. 

![](https://github.com/ASIGNATURA-ARCO-UCLM/lab3-bc-enriquealbalateprieto/blob/master/results/task2/tarea2Ejer2.png)
