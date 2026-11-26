# Comparación de rendimiento de ordenamientos

## Método

Se ejecutó `test/sorting_performance.cpp` compilado con g++ 14.2.0, C++11 y
optimización `-O2`. El programa genera datos sintéticos deterministas para
N = 100, 1.000, 5.000 y 10.000. Los algoritmos ordenan copias según nombre,
longitud, peso o edad. El programa valida el resultado y contabiliza
comparaciones y movimientos/intercambios. Los tiempos son milisegundos medidos
en el entorno de revisión; pueden variar en otro equipo.

## Resultados observados

| Algoritmo | N | Comparaciones | Tiempo (ms) | Validación | Intercambios/movimientos |
|---|---:|---:|---:|---|---:|
| Bubble Sort | 100 | 4.895 | 0,403 | OK | 2.503 |
| Selection Sort | 100 | 4.950 | 0,052 | OK | 95 |
| Insertion Sort | 100 | 2.452 | 0,076 | OK | 2.551 |
| Merge Sort (peso) | 100 | 497 | 0,049 | OK | 1.344 |
| Merge Sort (edad) | 100 | 538 | 0,044 | OK | 1.344 |
| Bubble Sort | 1.000 | 498.939 | 25,675 | OK | 251.205 |
| Selection Sort | 1.000 | 499.500 | 4,889 | OK | 991 |
| Insertion Sort | 1.000 | 251.245 | 7,714 | OK | 252.244 |
| Merge Sort (peso) | 1.000 | 8.203 | 0,698 | OK | 19.952 |
| Merge Sort (edad) | 1.000 | 8.621 | 0,722 | OK | 19.952 |
| Bubble Sort | 5.000 | 12.490.119 | 549,776 | OK | 6.245.575 |
| Selection Sort | 5.000 | 12.497.500 | 120,550 | OK | 4.989 |
| Insertion Sort | 5.000 | 6.246.229 | 156,862 | OK | 6.251.228 |
| Merge Sort (peso) | 5.000 | 53.239 | 3,411 | OK | 123.616 |
| Merge Sort (edad) | 5.000 | 55.263 | 3,432 | OK | 123.616 |
| Bubble Sort | 10.000 | 49.985.130 | 2.206,087 | OK | 25.016.941 |
| Selection Sort | 10.000 | 49.995.000 | 478,580 | OK | 9.987 |
| Insertion Sort | 10.000 | 24.967.459 | 625,978 | OK | 24.977.458 |
| Merge Sort (peso) | 10.000 | 116.473 | 8,157 | OK | 267.232 |
| Merge Sort (edad) | 10.000 | 120.501 | 7,461 | OK | 267.232 |

## Análisis

- **Bubble Sort - O(n²):** compara elementos vecinos y los intercambia cuando
  están fuera de orden. La salida temprana ayuda si una pasada no realiza
  intercambios, pero con datos desordenados el costo crece rápidamente. Para
  N=10.000 tomó aproximadamente 2,2 segundos en esta ejecución.
- **Selection Sort - O(n²):** busca el mínimo restante para cada posición.
  Hace muchas comparaciones incluso con entradas ordenadas, aunque realiza
  pocos intercambios (como máximo uno por posición). En la medición fue más
  rápido que Bubble e Insertion, pero sigue teniendo crecimiento cuadrático.
- **Insertion Sort - O(n²) promedio/peor, O(n) mejor:** inserta cada elemento
  en la parte izquierda ya ordenada. Es sencillo y puede ser competitivo con
  arreglos pequeños o casi ordenados; en datos sintéticos de 10.000 elementos
  superó los 625 ms.
- **Merge Sort - O(n log n):** divide el arreglo, ordena las mitades y las
  combina. Requiere memoria auxiliar O(n), pero su crecimiento fue mucho menor:
  alrededor de 7-8 ms para 10.000 registros en esta ejecución.

## Conclusión

Para conjuntos grandes, Merge Sort es la opción más adecuada de las medidas
realizadas por su complejidad O(n log n) y sus tiempos observados. Bubble,
Selection e Insertion son útiles para estudiar técnicas básicas y pueden ser
suficientes con pocos datos, pero no escalan igual. No se deben presentar los
milisegundos como una garantía universal: dependen del hardware, compilador,
optimización, datos y carga del sistema. El benchmark valida el orden final
(`OK`), pero no sustituye pruebas de estabilidad ni análisis de memoria.
