# DinoRegistry — Jurassic Data Park

Aplicación de consola en C++ para administrar registros de dinosaurios. Este repositorio conserva **programación procedural** con `struct`, funciones y arreglos dinámicos administrados con `new[]` y `delete[]`; no utiliza clases ni `std::vector` para la colección principal.

## Información académica

- **Estudiante:** Isabella Cruz Quintero
- **Docente:** John Harold Morales Velez
- **Asignatura:** Validación - Técnicas de Programación
- **Fecha de documentación:** 25 de noviembre de 2026
- **Versión documental:** 1.0.0 (no crea una release ni un tag de Git)

## Funcionalidades

- Agregar, editar, eliminar, listar y consultar dinosaurios.
- Validar códigos y evitar registros duplicados.
- Buscar por nombre y realizar conteos de texto.
- Ordenar por nombre, longitud, peso y edad con Bubble, Selection, Insertion y Merge Sort.
- Cargar y guardar datos en archivos de texto y generar un reporte.
- Analizar una cuadrícula de excavación.
- Ejecutar retos de búsqueda, recursividad y otros algoritmos.

## Estructura del repositorio

```text
DinoRegistry/
├── docs/       # Formatos, casos de prueba y análisis de rendimiento
├── include/    # Encabezados (.h)
├── src/        # Implementaciones (.cpp) y main.cpp
├── test/       # Pruebas automatizadas y benchmark
├── dinosaurs.txt
├── excavation.txt
├── README.md
└── README.txt
```

## Requisitos

- Compilador `g++` compatible con C++11 o superior.
- Terminal abierta en la carpeta raíz del proyecto.

## Compilar y ejecutar

### Windows PowerShell (MSYS2 UCRT64 / MinGW-w64)

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o DinoRegistry.exe
.\DinoRegistry.exe
```

Para compilar y ejecutar sin dejar el ejecutable en la carpeta del repositorio:

```powershell
$exe = "$env:TEMP\DinoRegistry.exe"
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o $exe
if ($LASTEXITCODE -eq 0) { & $exe; Remove-Item $exe -ErrorAction SilentlyContinue }
```

### Linux / macOS

```bash
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude src/main.cpp src/dinosaur.cpp src/dinosaur_collection.cpp src/dinosaur_management.cpp src/dinosaur_console.cpp src/dinosaur_search.cpp src/file_persistence.cpp src/dinosaur_sorting.cpp src/excavation_map.cpp src/recursive_challenges.cpp -o DinoRegistry
./DinoRegistry
```

Ejecuta siempre desde la raíz para que las rutas relativas de `dinosaurs.txt` y `excavation.txt` se resuelvan correctamente.

## Pruebas

Las instrucciones y los estados de cada caso se encuentran en [`docs/test-cases.md`](docs/test-cases.md). Los formatos de datos están en [`docs/file-formats.md`](docs/file-formats.md), y la comparación de algoritmos en [`docs/sorting-performance.md`](docs/sorting-performance.md).

Ejemplo para compilar las pruebas del mapa en Windows:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/excavation_map_tests.cpp src/excavation_map.cpp -o map_tests.exe
.\map_tests.exe
```

Ejemplo para las pruebas de retos:

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic -Iinclude test/recursive_challenges_tests.cpp src/recursive_challenges.cpp src/dinosaur_management.cpp src/dinosaur_collection.cpp src/dinosaur_search.cpp src/dinosaur_sorting.cpp -o recursive_tests.exe
.\recursive_tests.exe
```

## Formatos de datos

- `dinosaurs.txt`: ocho campos separados por `|` en cada línea.
- `excavation.txt`: dimensiones seguidas por los valores numéricos de la matriz.
- `report.txt`: archivo de salida generado por el programa.

Consulta [`docs/file-formats.md`](docs/file-formats.md) antes de editar los archivos manualmente.

## Estado de pruebas y alcance

La documentación separa pruebas ejecutadas de pruebas pendientes. Los resultados guardados en `docs/*-result.txt` corresponden a las ejecuciones registradas durante la revisión; no deben interpretarse como resultados de cualquier equipo o versión local posterior.

No se ha creado `release/1.0.0` ni un tag de Git.
