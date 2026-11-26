DINOREGISTRY - JURASSIC DATA PARK
=================================
Version del proyecto: 1.0.0 (identificador documental; no crea un tag ni release)
Fecha de revision: 25 de noviembre de 2026
Estudiante: Isabella Cruz Quintero
Docente: John Harold Morales Velez
Asignatura: Validacion - Tecnicas de Programacion

1. DESCRIPCION
DinoRegistry es una aplicacion de consola en C++ para administrar registros
sobre dinosaurios. Incluye operaciones de alta, consulta, edicion y eliminacion;
busquedas por codigo y nombre; ordenamientos; lectura y escritura de archivos;
analisis de un mapa numerico de excavacion y ejercicios algoritmicos.

2. REQUISITOS
- Compilador g++ compatible con C++11 o superior.
- Terminal ubicada en la carpeta raiz del proyecto.
- Los archivos dinosaurs.txt y excavation.txt deben estar en esa carpeta
  para cargar los datos de ejemplo y el mapa.

3. ESTRUCTURA
include/  Encabezados y declaraciones de estructuras y funciones.
src/      Implementaciones y funcion main.
test/     Pruebas automatizadas y programa de medicion de ordenamientos.
docs/     Formatos de datos, casos de prueba y analisis de rendimiento.

4. COMPILAR EN LINUX / macOS / MSYS2 UCRT64
Desde la raiz del proyecto ejecutar:

g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude \
  src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp \
  src/dinosaur_management.cpp src/dinosaur_console.cpp \
  src/dinosaur_search.cpp src/file_persistence.cpp \
  src/dinosaur_sorting.cpp src/excavation_map.cpp \
  src/recursive_challenges.cpp -o DinoRegistry

Ejecutar:
./DinoRegistry

5. COMPILAR EN WINDOWS POWERSHELL
Desde la raiz del proyecto:

g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o DinoRegistry.exe

Ejecutar:
.\DinoRegistry.exe

Windows genera un ejecutable PE con extension .exe. Omitir la extension en
-o no evita que Windows la agregue. Si no se desea guardar el ejecutable dentro
del repositorio, puede compilarse en la carpeta temporal:

$exe = "$env:TEMP\DinoRegistry.exe"
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o $exe
if ($LASTEXITCODE -eq 0) { & $exe; Remove-Item $exe -ErrorAction SilentlyContinue }

6. PRUEBAS AUTOMATIZADAS
Desde la raiz, compilar y ejecutar:

g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/excavation_map_tests.cpp src/excavation_map.cpp -o map_tests
./map_tests

 g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/recursive_challenges_tests.cpp src/recursive_challenges.cpp src/dinosaur_management.cpp src/dinosaur_collection.cpp src/dinosaur_search.cpp src/dinosaur_sorting.cpp -o recursive_tests
./recursive_tests

En Windows sustituir ./nombre por .\nombre.exe y agregar -o nombre.exe.
Los casos adicionales y resultados medidos se documentan en docs/test-cases.md
y docs/sorting-performance.md.

7. ARCHIVOS DE DATOS
- dinosaurs.txt: ocho campos por linea separados por |. Ver docs/file-formats.md.
- excavation.txt: dimensiones y matriz de enteros no negativos.
- report.txt: salida generada al salir; no requiere edicion manual.
Las rutas son relativas al directorio actual. Ejecutar desde la raiz.

8. MODELO Y RESTRICCIONES
La coleccion principal usa DinosaurCollection con arreglo dinamico, puntero,
count y capacity. La memoria se reserva con new[] y se libera con delete[].
La solucion conserva programacion procedural con struct y funciones; no usa
clases ni std::vector para la coleccion principal.

9. ESTADO DE VALIDACION
La compilacion de la aplicacion y los programas de prueba, las pruebas incluidas
de mapa y retos, una prueba adicional de gestion/busqueda/persistencia/mapas y
una ejecucion de arranque/salida se ejecutaron durante esta revision. Las
pruebas manuales interactivas completas y una medicion con sanitizadores o
Valgrind quedan pendientes. Consultar docs/test-cases.md para el detalle.
