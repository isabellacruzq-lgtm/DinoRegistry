#include "excavation_map.h"

#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <string>

// Convierte una fila y una columna en una posición del arreglo.
static std::size_t getIndex(
    const ExcavationMap& map,
    std::size_t row,
    std::size_t column
) {
    return row * map.columns + column;
}

// Suma las celdas de una fila.
static long long calculateRowTotal(
    const ExcavationMap& map,
    std::size_t row
) {
    long long total = 0;

    for (std::size_t column = 0;
         column < map.columns;
         ++column) {
        total += getMapValue(map, row, column);
    }

    return total;
}

// Suma las celdas de una columna.
static long long calculateColumnTotal(
    const ExcavationMap& map,
    std::size_t column
) {
    long long total = 0;

    for (std::size_t row = 0; row < map.rows; ++row) {
        total += getMapValue(map, row, column);
    }

    return total;
}

// Suma un bloque de 3 x 3 desde una posición inicial.
static long long calculateThreeByThreeTotal(
    const ExcavationMap& map,
    std::size_t startRow,
    std::size_t startColumn
) {
    long long total = 0;

    for (std::size_t row = startRow; row < startRow + 3; ++row) {
        for (std::size_t column = startColumn;
             column < startColumn + 3;
             ++column) {
            total += getMapValue(map, row, column);
        }
    }

    return total;
}

// Busca el máximo en un segmento del arreglo.
// Divide el segmento en dos partes y combina ambos máximos.
static int findMaximumRecursive(
    const int* cells,
    std::size_t left,
    std::size_t right
) {
    if (left == right) {
        return cells[left];
    }

    const std::size_t middle = left + (right - left) / 2;

    const int leftMaximum =
        findMaximumRecursive(cells, left, middle);

    const int rightMaximum =
        findMaximumRecursive(cells, middle + 1, right);

    return leftMaximum > rightMaximum
        ? leftMaximum
        : rightMaximum;
}

/*
 * Carga las dimensiones y los valores del mapa.
 * Rechaza dimensiones inválidas, valores negativos, datos faltantes
 * y contenido adicional después de la matriz.
 * Devuelve true si la carga fue exitosa.
 * Complejidad: O(filas * columnas).
 */
bool loadExcavationMap(
    const char* filename,
    ExcavationMap& map
) {
    map.cells = nullptr;
    map.rows = 0;
    map.columns = 0;

    std::ifstream input(filename);

    if (!input.is_open()) {
        std::cerr << "No se pudo abrir el archivo: "
                  << filename << '\n';
        return false;
    }

    long long rowsRead;
    long long columnsRead;

    if (!(input >> rowsRead >> columnsRead)
        || rowsRead <= 0
        || columnsRead <= 0) {
        std::cerr << "El archivo está vacío o sus dimensiones "
                  << "son inválidas.\n";
        return false;
    }

    const unsigned long long maxSize =
        static_cast<unsigned long long>(
            std::numeric_limits<std::size_t>::max()
        );

    if (static_cast<unsigned long long>(rowsRead) > maxSize
        || static_cast<unsigned long long>(columnsRead) > maxSize) {
        std::cerr << "Las dimensiones del mapa son demasiado grandes.\n";
        return false;
    }

    const std::size_t rows =
        static_cast<std::size_t>(rowsRead);
    const std::size_t columns =
        static_cast<std::size_t>(columnsRead);

    if (rows > std::numeric_limits<std::size_t>::max() / columns) {
        std::cerr << "Las dimensiones del mapa son demasiado grandes.\n";
        return false;
    }

    const std::size_t cellCount = rows * columns;

    int* cells = new (std::nothrow) int[cellCount];

    if (cells == nullptr) {
        std::cerr << "No hay memoria suficiente para cargar el mapa.\n";
        return false;
    }

    for (std::size_t i = 0; i < cellCount; ++i) {
        long long value;

        if (!(input >> value) || value < 0
            || value > std::numeric_limits<int>::max()) {
            std::cerr << "El mapa contiene datos faltantes "
                      << "o valores inválidos.\n";
            delete[] cells;
            return false;
        }

        cells[i] = static_cast<int>(value);
    }

    std::string extraData;

    if (input >> extraData) {
        std::cerr << "El archivo contiene datos adicionales "
                  << "después del mapa.\n";
        delete[] cells;
        return false;
    }

    map.cells = cells;
    map.rows = rows;
    map.columns = columns;

    return true;
}

/*
 * Libera la memoria dinámica del mapa.
 * No devuelve valor.
 * Complejidad: O(1).
 */
void freeExcavationMap(ExcavationMap& map) {
    delete[] map.cells;

    map.cells = nullptr;
    map.rows = 0;
    map.columns = 0;
}

/*
 * Obtiene una celda del mapa.
 * Precondición: los índices deben estar dentro de las dimensiones.
 * Complejidad: O(1).
 */
int getMapValue(
    const ExcavationMap& map,
    std::size_t row,
    std::size_t column
) {
    return map.cells[getIndex(map, row, column)];
}

/*
 * Imprime el mapa completo.
 * Complejidad: O(filas * columnas).
 */
void displayExcavationMap(const ExcavationMap& map) {
    if (map.cells == nullptr || map.rows == 0 || map.columns == 0) {
        std::cout << "El mapa está vacío.\n";
        return;
    }

    std::cout << "\nMapa de excavación ("
              << map.rows << " x " << map.columns << "):\n";

    for (std::size_t row = 0; row < map.rows; ++row) {
        for (std::size_t column = 0;
             column < map.columns;
             ++column) {
            std::cout << getMapValue(map, row, column) << '\t';
        }

        std::cout << '\n';
    }
}

/*
 * Suma todos los valores del mapa.
 * Devuelve el total de fósiles.
 * Complejidad: O(filas * columnas).
 */
long long calculateTotalFossils(const ExcavationMap& map) {
    long long total = 0;
    const std::size_t cellCount = map.rows * map.columns;

    for (std::size_t i = 0; i < cellCount; ++i) {
        total += map.cells[i];
    }

    return total;
}

/*
 * Busca la fila con la suma mayor.
 * En caso de empate, devuelve la primera fila.
 * Complejidad: O(filas * columnas).
 */
std::size_t findRowWithMostFossils(
    const ExcavationMap& map,
    long long& rowTotal
) {
    std::size_t bestRow = 0;
    rowTotal = calculateRowTotal(map, 0);

    for (std::size_t row = 1; row < map.rows; ++row) {
        const long long total = calculateRowTotal(map, row);

        if (total > rowTotal) {
            rowTotal = total;
            bestRow = row;
        }
    }

    return bestRow;
}

/*
 * Busca la columna con la suma mayor.
 * En caso de empate, devuelve la primera columna.
 * Complejidad: O(filas * columnas).
 */
std::size_t findColumnWithMostFossils(
    const ExcavationMap& map,
    long long& columnTotal
) {
    std::size_t bestColumn = 0;
    columnTotal = calculateColumnTotal(map, 0);

    for (std::size_t column = 1;
         column < map.columns;
         ++column) {
        const long long total = calculateColumnTotal(map, column);

        if (total > columnTotal) {
            columnTotal = total;
            bestColumn = column;
        }
    }

    return bestColumn;
}

/*
 * Revisa todas las posiciones posibles de un bloque 3 x 3.
 * Devuelve false si no existe un bloque de ese tamaño.
 * Complejidad: O(filas * columnas).
 */
bool findBestThreeByThreeArea(
    const ExcavationMap& map,
    std::size_t& bestRow,
    std::size_t& bestColumn,
    long long& bestTotal
) {
    if (map.cells == nullptr || map.rows < 3 || map.columns < 3) {
        return false;
    }

    bestRow = 0;
    bestColumn = 0;
    bestTotal = calculateThreeByThreeTotal(map, 0, 0);

    for (std::size_t row = 0; row <= map.rows - 3; ++row) {
        for (std::size_t column = 0;
             column <= map.columns - 3;
             ++column) {
            const long long total =
                calculateThreeByThreeTotal(map, row, column);

            if (total > bestTotal) {
                bestTotal = total;
                bestRow = row;
                bestColumn = column;
            }
        }
    }

    return true;
}

/*
 * Encuentra el valor máximo mediante divide y vencerás.
 * Divide el arreglo en mitades, encuentra el máximo de cada mitad
 * y devuelve el mayor de los dos resultados.
 * Complejidad temporal: O(filas * columnas).
 */
int findMaximumDivideAndConquer(const ExcavationMap& map) {
    const std::size_t cellCount = map.rows * map.columns;

    if (map.cells == nullptr || cellCount == 0) {
        return 0;
    }

    return findMaximumRecursive(map.cells, 0, cellCount - 1);
}

/*
 * Presenta las opciones de análisis del mapa.
 * Carga el archivo al entrar y libera la memoria al salir.
 */
void runExcavationMapMenu(const char* filename) {
    ExcavationMap map = {nullptr, 0, 0};

    if (!loadExcavationMap(filename, map)) {
        std::cout << "No se puede analizar el mapa.\n";
        return;
    }

    bool running = true;

    while (running) {
        std::cout
            << "\n===== Análisis del mapa de excavación =====\n"
            << "1. Mostrar mapa completo\n"
            << "2. Calcular total de fósiles\n"
            << "3. Fila con más fósiles\n"
            << "4. Columna con más fósiles\n"
            << "5. Área de 3 x 3 con más fósiles\n"
            << "6. Máximo mediante divide y vencerás\n"
            << "0. Volver al menú principal\n"
            << "Opción: ";

        int option;

        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                break;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cout << "Debes escribir un número.\n";
            continue;
        }

        switch (option) {
            case 1:
                displayExcavationMap(map);
                break;

            case 2:
                std::cout << "Total de fósiles: "
                          << calculateTotalFossils(map) << '\n';
                break;

            case 3: {
                long long total;
                const std::size_t row =
                    findRowWithMostFossils(map, total);

                std::cout << "Fila con más fósiles: " << row + 1
                          << " (total: " << total << ")\n";
                break;
            }

            case 4: {
                long long total;
                const std::size_t column =
                    findColumnWithMostFossils(map, total);

                std::cout << "Columna con más fósiles: " << column + 1
                          << " (total: " << total << ")\n";
                break;
            }

            case 5: {
                std::size_t row;
                std::size_t column;
                long long total;

                if (findBestThreeByThreeArea(
                        map, row, column, total)) {
                    std::cout << "Mejor área 3 x 3: comienza en fila "
                              << row + 1 << ", columna " << column + 1
                              << ". Total: " << total << '\n';
                } else {
                    std::cout
                        << "No se puede buscar un área 3 x 3: "
                        << "el mapa tiene menos de 3 filas o columnas.\n";
                }
                break;
            }

            case 6:
                std::cout << "Valor máximo: "
                          << findMaximumDivideAndConquer(map) << '\n';
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    }

    freeExcavationMap(map);
}
