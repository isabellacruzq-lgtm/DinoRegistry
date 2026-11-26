# Plan y resultados de pruebas - DinoRegistry

Fecha de ejecución: 25 de noviembre de 2026. Entorno de revisión: Linux,
g++ 14.2.0, compilación C++11 con `-Wall -Wextra -pedantic`.

**Estados:** EJECUTADA = se ejecutó y se observó el resultado indicado;
PENDIENTE = no se ejecutó en esta revisión; NO APLICA = no corresponde.
No se marca una prueba como aprobada por inspección visual del código.

| ID | Funcionalidad | Entrada / procedimiento | Resultado esperado | Resultado obtenido | Estado |
|---|---|---|---|---|---|
| TC-001 | Compilación general | Compilar todos los `.cpp` de `src` con C++11 y advertencias | Ejecutable generado, sin errores ni advertencias | Compilación finalizó con código 0; sin mensajes del compilador | EJECUTADA |
| TC-002 | Pruebas de mapa | Compilar y ejecutar `test/excavation_map_tests.cpp` | Mensaje de éxito; asserts pasan | `Todas las pruebas del mapa pasaron.` | EJECUTADA |
| TC-003 | Pruebas de retos | Compilar y ejecutar `test/recursive_challenges_tests.cpp` y dependencias | Mensaje de éxito; asserts pasan | `Todas las pruebas de retos pasaron.` | EJECUTADA |
| TC-004 | Colección vacía | Inicializar; buscar código inexistente | count=0, búsqueda devuelve -1 | En prueba adicional, estado inicial y búsqueda sin coincidencia pasaron | EJECUTADA |
| TC-005 | Un solo dinosaurio | Agregar un registro válido y consultar | count=1; consulta recupera el registro | En prueba adicional se agregó y recuperó por código sin distinguir mayúsculas | EJECUTADA |
| TC-006 | Código vacío | Intentar agregar registro con code vacío | Rechazar y conservar colección | Rechazado en prueba adicional | EJECUTADA |
| TC-007 | Código duplicado | Agregar dos registros con mismo código | Segundo registro rechazado | Rechazado en prueba adicional | EJECUTADA |
| TC-008 | Crecimiento de colección | Agregar 3 registros (capacidad inicial se duplica) | Ampliación conserva los registros | Tres altas, consulta, edición y eliminación pasaron; se ejercitó crecimiento | EJECUTADA |
| TC-009 | Edición de inexistente | Editar código que no existe | Devuelve false; no altera colección | Devuelve false en prueba adicional | EJECUTADA |
| TC-010 | Eliminación | Eliminar existente y luego intentar eliminarlo otra vez | Primera true; segunda false | Resultado observado conforme en prueba adicional | EJECUTADA |
| TC-011 | Búsqueda sin resultados | Buscar `nothing` | Total 0 | Total 0 en prueba adicional | EJECUTADA |
| TC-012 | Búsqueda múltiple | Buscar `alpha` en Alpha rex y Alpha minor | Dos coincidencias e índices válidos | Dos coincidencias en índices 0 y 1 | EJECUTADA |
| TC-013 | Búsqueda sin arreglo de salida | `results=nullptr`, `maxResults=0` | Cuenta coincidencias sin escribir índices | Devolvió 3 coincidencias en prueba adicional | EJECUTADA |
| TC-014 | Ordenamiento por nombre | Copia de colección con nombres repetidos/parciales y Bubble Sort | Resultado no decreciente | Se comprobó orden de copia en prueba adicional; no se ejecutó batería completa con duplicados para todos los algoritmos | EJECUTADA (alcance parcial) |
| TC-015 | Benchmark de ordenamientos | Ejecutar `sorting_performance` con n=100,1000,5000,10000 | Todos los algoritmos validan orden | Todos los renglones mostraron `OK` | EJECUTADA |
| TC-016 | Mapa 8x8 | Ejecutar pruebas existentes | Total 512, mejor fila/columna 7, bloque 3x3 suma 117, máximo 15 | Suite del mapa informó éxito | EJECUTADA |
| TC-017 | Mapa menor que 3x3 | Cargar archivo pequeño de prueba | No existe bloque 3x3 | Incluido en suite; suite informó éxito | EJECUTADA |
| TC-018 | Mapa inválido (dato no numérico/faltante) | Archivo temporal `2 2 / 1 2 / 3 nope` | Rechazar y liberar memoria | Rechazado con aviso de datos faltantes/inválidos; puntero nulo | EJECUTADA |
| TC-019 | Mapa con datos adicionales | Archivo temporal `1 1 / 7 8` | Rechazar datos sobrantes | Rechazado con aviso de datos adicionales | EJECUTADA |
| TC-020 | Persistencia | Guardar dos registros y volver a cargarlos | Recuperar mismos registros | Guardado y carga informaron dos registros | EJECUTADA |
| TC-021 | Archivo ausente `dinosaurs.txt` | Iniciar desde directorio sin archivo | Aviso y colección vacía; programa debe permitir continuar | No se hizo una prueba de sesión interactiva completa | PENDIENTE |
| TC-022 | Archivo de dinosaurios mal formado | Mezclar línea válida, inválida y código duplicado | Válida cargada; inválidas omitidas con aviso | No se ejecutó un archivo de prueba mixto completo | PENDIENTE |
| TC-023 | Archivo de mapa ausente | Menú de mapa con ruta inexistente | Mensaje y retorno seguro | No ejecutado como sesión interactiva | PENDIENTE |
| TC-024 | Entrada inválida del menú | Letras, opción fuera de rango, línea vacía | Rechazo y menú vuelve a solicitar | No ejecutado en esta revisión | PENDIENTE |
| TC-025 | Fin de entrada (EOF) | Ejecutar aplicación con stdin cerrado desde carpeta con datos | Guardar, reportar, liberar y salir | Cargó 3 registros, generó reporte, liberó memoria y salió con código 0 | EJECUTADA |
| TC-026 | Reporte con colección vacía | Generar reporte de colección vacía | Total 0 y mensaje de colección vacía | No probado de forma aislada | PENDIENTE |
| TC-027 | Límites Fibonacci | n=0,1,6,10,93,94 y puntero nulo | Resultados correctos; 94 y nullptr rechazados | Suite de retos pasó | EJECUTADA |
| TC-028 | Límites recursivos | Nombres vacíos, colección mayor al máximo, sumas y pares | No desbordar ni acceder fuera de rango | Parte de casos está cubierta por suite; no se cubrieron todos los límites documentados | PENDIENTE (cobertura ampliada) |
| TC-029 | Colecciones grandes | 10.000 registros sintéticos en benchmark | Orden correcto; observar crecimiento | Benchmark alcanzó n=10.000; todos los algoritmos validaron | EJECUTADA |
| TC-030 | Sanitizadores / fugas | Compilar con ASan/UBSan o ejecutar Valgrind | Sin errores de memoria | No ejecutado | PENDIENTE |
| TC-031 | Interacción CRUD completa | Recorrer todas las opciones con entradas de usuario | Operaciones coherentes de extremo a extremo | Solo se probó arranque y EOF; sesión interactiva completa pendiente | PENDIENTE |

## Reproducción

Desde la raíz del repositorio:

```bash
# Aplicación
 g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o DinoRegistry

# Mapa
 g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/excavation_map_tests.cpp src/excavation_map.cpp -o map_tests
 ./map_tests

# Retos
 g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/recursive_challenges_tests.cpp src/recursive_challenges.cpp src/dinosaur_management.cpp src/dinosaur_collection.cpp src/dinosaur_search.cpp src/dinosaur_sorting.cpp -o recursive_tests
 ./recursive_tests

# Rendimiento
 g++ -std=c++11 -O2 -Wall -Wextra -pedantic -Iinclude test/sorting_performance.cpp src/dinosaur_sorting.cpp -o sorting_performance
 ./sorting_performance
```

En PowerShell, ejecutar cada binario con ` .\nombre.exe ` y compilar usando
`-o nombre.exe`. Ejecutar desde la raíz porque las rutas de datos son relativas.
