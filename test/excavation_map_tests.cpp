#include "excavation_map.h"

#include <cassert>
#include <iostream>

// Comprueba las dimensiones y los resultados calculados para el mapa de ejemplo de 8 x 8.
static void testExampleMap() {
    // Inicializa el mapa vacío; loadExcavationMap lo llenará con los datos del archivo.
    ExcavationMap map = {nullptr, 0, 0};

    // Verifica que el archivo se cargó y que el mapa tiene las dimensiones esperadas.
    assert(loadExcavationMap("excavation.txt", map));
    assert(map.rows == 8);
    assert(map.columns == 8);

    // Comprueba la suma total de fósiles de todas las celdas.
    assert(calculateTotalFossils(map) == 512);

    // Busca la fila con más fósiles y verifica su índice y su suma.
    long long rowTotal = 0;
    const std::size_t bestRow =
        findRowWithMostFossils(map, rowTotal);

    assert(bestRow == 7);
    assert(rowTotal == 92);

    // Busca la columna con más fósiles y verifica su índice y su suma.
    long long columnTotal = 0;
    const std::size_t bestColumn =
        findColumnWithMostFossils(map, columnTotal);

    assert(bestColumn == 7);
    assert(columnTotal == 92);

    // Busca el bloque contiguo de 3 x 3 que contiene más fósiles.
    std::size_t startRow = 0;
    std::size_t startColumn = 0;
    long long areaTotal = 0;

    assert(findBestThreeByThreeArea(
        map, startRow, startColumn, areaTotal
    ));

    assert(startRow == 5);
    assert(startColumn == 5);
    assert(areaTotal == 117);

    // Comprueba el máximo obtenido mediante el algoritmo de divide y vencerás.
    assert(findMaximumDivideAndConquer(map) == 15);

    // Libera la memoria y comprueba que el mapa quedó en su estado vacío.
    freeExcavationMap(map);
    assert(map.cells == nullptr);
    assert(map.rows == 0);
    assert(map.columns == 0);
}

// Comprueba que un mapa menor de 3 x 3 no tenga área válida.
static void testSmallMap() {
    // Inicializa y carga el mapa pequeño desde el archivo de prueba.
    ExcavationMap map = {nullptr, 0, 0};

    assert(loadExcavationMap("test/excavation_small.txt", map));

    // Prepara las variables de salida para la búsqueda del bloque de 3 x 3.
    std::size_t row = 0;
    std::size_t column = 0;
    long long total = 0;

    // La búsqueda debe fallar porque el mapa no alcanza las dimensiones requeridas.
    assert(!findBestThreeByThreeArea(
        map, row, column, total
    ));

    // Comprueba el valor esperado del algoritmo de divide y vencerás para este mapa.
    assert(findMaximumDivideAndConquer(map) == 9);

    // Libera los recursos utilizados por el mapa pequeño.
    freeExcavationMap(map);
}

int main() {
    // Ejecuta las pruebas para el mapa de ejemplo y para el mapa pequeño.
    testExampleMap();
    testSmallMap();

    // Muestra un mensaje cuando todas las aserciones se han cumplido.
    std::cout << "Todas las pruebas del mapa pasaron.\n";
    return 0;
}
