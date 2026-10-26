#ifndef EXCAVATION_MAP_H
#define EXCAVATION_MAP_H

#include <cstddef>

// Representa un mapa de excavación de dimensiones variables.
// Los valores se almacenan en un arreglo dinámico de una dimensión.
struct ExcavationMap {
    int* cells;
    std::size_t rows;
    std::size_t columns;
};

// Carga y valida el mapa desde un archivo.
// Devuelve true si el archivo contiene un mapa válido.
bool loadExcavationMap(
    const char* filename,
    ExcavationMap& map
);

// Libera la memoria del mapa y reinicia sus dimensiones.
void freeExcavationMap(ExcavationMap& map);

// Obtiene el valor de una celda mediante su fila y columna,
// usando índices que comienzan en cero.
int getMapValue(
    const ExcavationMap& map,
    std::size_t row,
    std::size_t column
);

// Muestra todas las celdas del mapa.
void displayExcavationMap(const ExcavationMap& map);

// Suma todos los fósiles del mapa.
long long calculateTotalFossils(const ExcavationMap& map);

// Encuentra la fila con la suma más alta.
// Devuelve su índice desde cero y guarda la suma en rowTotal.
std::size_t findRowWithMostFossils(
    const ExcavationMap& map,
    long long& rowTotal
);

// Encuentra la columna con la suma más alta.
// Devuelve su índice desde cero y guarda la suma en columnTotal.
std::size_t findColumnWithMostFossils(
    const ExcavationMap& map,
    long long& columnTotal
);

// Encuentra el bloque de 3 x 3 con mayor suma.
// Guarda su fila inicial, columna inicial y suma.
// Devuelve false si el mapa es menor de 3 x 3.
bool findBestThreeByThreeArea(
    const ExcavationMap& map,
    std::size_t& bestRow,
    std::size_t& bestColumn,
    long long& bestTotal
);

// Encuentra el máximo usando divide y vencerás.
int findMaximumDivideAndConquer(
    const ExcavationMap& map
);

// Carga el mapa y presenta las opciones de análisis.
void runExcavationMapMenu(const char* filename);

#endif
