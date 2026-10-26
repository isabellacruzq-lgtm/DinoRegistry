#ifndef DINOSAUR_SORTING_H
#define DINOSAUR_SORTING_H

#include "dinosaur_collection.h"

#include <cstddef>

/*
 * Guarda las estadísticas de un algoritmo de ordenamiento.
 *
 * comparisons: cantidad de comparaciones entre valores.
 * swaps: intercambios completos de dos elementos.
 * movements: asignaciones o movimientos de elementos.
 */
struct SortStats {
    unsigned long long comparisons;
    unsigned long long swaps;
    unsigned long long movements;

    SortStats()
        : comparisons(0), swaps(0), movements(0) {}
};

/*
 * Crea una copia de los dinosaurios de la colección.
 * La colección original no se modifica.
 *
 * El usuario que recibe la copia debe liberarla con delete[].
 */
Dinosaur* copyDinosaursForSorting(
    const DinosaurCollection& collection
);

/*
 * Bubble Sort por nombre.
 *
 * Tiempo:
 *   Mejor caso: O(n), si ya está ordenado.
 *   Promedio y peor caso: O(n^2).
 * Espacio auxiliar: O(1), sin contar la copia.
 */
void bubbleSortByName(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
);

/*
 * Selection Sort por nombre.
 *
 * Tiempo: O(n^2) en mejor, promedio y peor caso.
 * Espacio auxiliar: O(1), sin contar la copia.
 */
void selectionSortByName(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
);

/*
 * Insertion Sort por longitud, de menor a mayor.
 *
 * Tiempo:
 *   Mejor caso: O(n).
 *   Promedio y peor caso: O(n^2).
 * Espacio auxiliar: O(1), sin contar la copia.
 */
void insertionSortByLength(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
);

/*
 * Merge Sort por peso, de menor a mayor.
 *
 * Tiempo: O(n log n) en todos los casos.
 * Espacio auxiliar: O(n) por el arreglo temporal.
 */
void mergeSortByWeight(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
);

/*
 * Merge Sort por edad, de menor a mayor.
 *
 * Tiempo: O(n log n) en todos los casos.
 * Espacio auxiliar: O(n) por el arreglo temporal.
 */
void mergeSortByAge(
    Dinosaur* items,
    std::size_t count,
    SortStats& stats
);

#endif
