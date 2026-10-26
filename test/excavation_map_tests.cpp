#include "excavation_map.h"

#include <cassert>
#include <iostream>

// Comprueba los resultados del mapa de ejemplo de 8 x 8.
static void testExampleMap() {
    ExcavationMap map = {nullptr, 0, 0};

    assert(loadExcavationMap("excavation.txt", map));
    assert(map.rows == 8);
    assert(map.columns == 8);

    assert(calculateTotalFossils(map) == 512);

    long long rowTotal = 0;
    const std::size_t bestRow =
        findRowWithMostFossils(map, rowTotal);

    assert(bestRow == 7);
    assert(rowTotal == 92);

    long long columnTotal = 0;
    const std::size_t bestColumn =
        findColumnWithMostFossils(map, columnTotal);

    assert(bestColumn == 7);
    assert(columnTotal == 92);

    std::size_t startRow = 0;
    std::size_t startColumn = 0;
    long long areaTotal = 0;

    assert(findBestThreeByThreeArea(
        map, startRow, startColumn, areaTotal
    ));

    assert(startRow == 5);
    assert(startColumn == 5);
    assert(areaTotal == 117);

    assert(findMaximumDivideAndConquer(map) == 15);

    freeExcavationMap(map);
    assert(map.cells == nullptr);
    assert(map.rows == 0);
    assert(map.columns == 0);
}

// Comprueba que un mapa menor de 3 x 3 no tenga área válida.
static void testSmallMap() {
    ExcavationMap map = {nullptr, 0, 0};

    assert(loadExcavationMap("test/excavation_small.txt", map));

    std::size_t row = 0;
    std::size_t column = 0;
    long long total = 0;

    assert(!findBestThreeByThreeArea(
        map, row, column, total
    ));

    assert(findMaximumDivideAndConquer(map) == 9);

    freeExcavationMap(map);
}

int main() {
    testExampleMap();
    testSmallMap();

    std::cout << "Todas las pruebas del mapa pasaron.\n";
    return 0;
}
