#include "dinosaur_sorting.h"

#include <string>

/*
 * Devuelve una copia independiente de la colección.
 */
Dinosaur* copyDinosaursForSorting(
    const DinosaurCollection& collection
) {
    if (collection.count == 0) {
        return nullptr;
    }

    Dinosaur* copy = new Dinosaur[collection.count];

    for (std::size_t i = 0; i < collection.count; ++i) {
        copy[i] = collection.items[i];
    }

    return copy;
}

/*
 * Intercambia dos dinosaurios completos.
 * Cada intercambio se cuenta como un swap y tres movimientos.
 */
static void swapDinosaurs(
    Dinosaur& first,
    Dinosaur& second,
    SortStats& stats
) {
    Dinosaur temporary = first;
    first = second;
    second = temporary;

    ++stats.swaps;
    stats.movements += 3;
}

/*
 * BUBBLE SORT POR NOMBRE
 *
 * Compara elementos vecinos.
 * Si están en el orden incorrecto, los intercambia.
 */
void bubbleSortByName(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
) {
    if (items == nullptr || count < 2) {
        return;
    }

    for (std::size_t end = count - 1; end > 0; --end) {
        bool swapped = false;

        for (std::size_t i = 0; i < end; ++i) {
            ++stats.comparisons;

            if (items[i].name > items[i + 1].name) {
                swapDinosaurs(items[i], items[i + 1], stats);
                swapped = true;
            }
        }

        // Si no hubo intercambios, ya está ordenado.
        if (!swapped) {
            break;
        }
    }
}

/*
 * SELECTION SORT POR NOMBRE
 *
 * Busca el nombre menor de la parte no ordenada
 * y lo coloca en la posición actual.
 */
void selectionSortByName(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
) {
    if (items == nullptr || count < 2) {
        return;
    }

    for (std::size_t i = 0; i < count - 1; ++i) {
        std::size_t smallest = i;

        for (std::size_t j = i + 1; j < count; ++j) {
            ++stats.comparisons;

            if (items[j].name < items[smallest].name) {
                smallest = j;
            }
        }

        if (smallest != i) {
            swapDinosaurs(items[i], items[smallest], stats);
        }
    }
}

/*
 * INSERTION SORT POR LONGITUD
 *
 * Guarda un elemento y lo inserta en la posición correcta
 * dentro de la parte izquierda, que ya está ordenada.
 */
void insertionSortByLength(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
) {
    if (items == nullptr || count < 2) {
        return;
    }

    for (std::size_t i = 1; i < count; ++i) {
        Dinosaur current = items[i];
        ++stats.movements;

        std::size_t j = i;

        while (j > 0) {
            ++stats.comparisons;

            if (items[j - 1].lengthMeters <= current.lengthMeters) {
                break;
            }

            items[j] = items[j - 1];
            ++stats.movements;
            --j;
        }

        items[j] = current;
        ++stats.movements;
    }
}

/*
 * Función auxiliar de Merge Sort.
 *
 * Criterio:
 *   0 = peso
 *   1 = edad
 */
static bool comesBeforeOrEqual(
    const Dinosaur& first,
    const Dinosaur& second,
    int criterion
) {
    if (criterion == 0) {
        return first.weightTons <= second.weightTons;
    }

    return first.ageMillionsYears <= second.ageMillionsYears;
}

/*
 * COMBINA DOS MITADES YA ORDENADAS.
 *
 * La mitad izquierda va desde left hasta middle.
 * La mitad derecha va desde middle + 1 hasta right.
 */
static void merge(
    Dinosaur* items,
    Dinosaur* temporary,
    std::size_t left,
    std::size_t middle,
    std::size_t right,
    int criterion,
    SortStats& stats
) {
    std::size_t i = left;
    std::size_t j = middle + 1;
    std::size_t k = left;

    // Compara ambas mitades y copia el elemento menor.
    while (i <= middle && j <= right) {
        ++stats.comparisons;

        if (comesBeforeOrEqual(items[i], items[j], criterion)) {
            temporary[k] = items[i];
            ++i;
        } else {
            temporary[k] = items[j];
            ++j;
        }

        ++k;
        ++stats.movements;
    }

    // Copia los elementos restantes de la mitad izquierda.
    while (i <= middle) {
        temporary[k] = items[i];
        ++i;
        ++k;
        ++stats.movements;
    }

    // Copia los elementos restantes de la mitad derecha.
    while (j <= right) {
        temporary[k] = items[j];
        ++j;
        ++k;
        ++stats.movements;
    }

    // Copia la sección combinada de vuelta al arreglo original.
    for (std::size_t position = left;
         position <= right;
         ++position) {
        items[position] = temporary[position];
        ++stats.movements;
    }
}

/*
 * Divide recursivamente el arreglo en mitades.
 *
 * Primero ordena la mitad izquierda.
 * Después ordena la mitad derecha.
 * Finalmente combina ambas mitades.
 */
static void mergeSortRecursive(
    Dinosaur* items,
    Dinosaur* temporary,
    std::size_t left,
    std::size_t right,
    int criterion,
    SortStats& stats
) {
    if (left >= right) {
        return;
    }

    // Evita posibles desbordamientos al calcular el punto medio.
    const std::size_t middle = left + (right - left) / 2;

    mergeSortRecursive(
        items, temporary, left, middle, criterion, stats
    );

    mergeSortRecursive(
        items, temporary, middle + 1, right, criterion, stats
    );

    merge(
        items, temporary, left, middle, right, criterion, stats
    );
}

/*
 * Función general para ejecutar Merge Sort.
 */
static void runMergeSort(
    Dinosaur* items,
    std::size_t count,
    int criterion,
    SortStats& stats
) {
    if (items == nullptr || count < 2) {
        return;
    }

    Dinosaur* temporary = new Dinosaur[count];

    mergeSortRecursive(
        items,
        temporary,
        0,
        count - 1,
        criterion,
        stats
    );

    delete[] temporary;
}

/*
 * Merge Sort por peso.
 */
void mergeSortByWeight(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
) {
    runMergeSort(items, count, 0, stats);
}

/*
 * Merge Sort por edad.
 */
void mergeSortByAge(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
) {
    runMergeSort(items, count, 1, stats);
}
