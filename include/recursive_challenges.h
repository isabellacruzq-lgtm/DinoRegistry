#ifndef RECURSIVE_CHALLENGES_H
#define RECURSIVE_CHALLENGES_H

#include "dinosaur_collection.h"

#include <cstddef>
#include <cstdint>
#include <string>

// Límites para evitar valores que desborden o recursiones demasiado grandes.
const unsigned int MAX_FIBONACCI_N = 93;
const std::size_t MAX_RECURSIVE_ITEMS = 10000;

// Calcula Fibonacci desde los casos pequeños hasta n.
// Devuelve false si n supera el límite o el puntero de salida es nulo.
// Tiempo O(n), espacio O(1).
bool calculateFibonacciBottomUp(
    unsigned int n,
    std::uint64_t* result
);

// Comprueba recursivamente si un nombre es palíndromo.
// Ignora espacios y diferencias entre mayúsculas y minúsculas.
// Devuelve false si el nombre está vacío.
// Tiempo O(m), espacio O(m) por la copia normalizada y O(m) de pila.
bool isDinosaurNamePalindrome(const std::string& name);

// Suma recursivamente el peso de la colección.
// Devuelve false si la colección supera el límite o no es válida.
// Tiempo O(n), espacio O(n) por la pila recursiva.
bool calculateTotalWeightRecursive(
    const DinosaurCollection& collection,
    double* totalWeight
);

// Busca dos dinosaurios distintos cuyas longitudes sumen el objetivo.
// Devuelve sus índices en firstIndex y secondIndex.
// Tiempo O(n^2), espacio O(1).
bool findLengthPairBruteForce(
    const DinosaurCollection& collection,
    double targetLength,
    std::size_t* firstIndex,
    std::size_t* secondIndex
);

// Suma recursivamente las filas de una formación de Pteranodons.
// La fila i contiene i individuos; n=0 produce cero.
// Tiempo O(n), espacio O(n) por la pila recursiva.
bool calculatePteranodonFormation(
    unsigned int rows,
    std::uint64_t* total
);

// Busca por código mediante búsqueda binaria recursiva.
// Ordena una copia por código para no modificar la colección original.
// Tiempo O(n^2) para preparar la copia y O(log n) para buscar.
// Espacio O(n) para la copia y O(log n) para la recursión.
bool findDinosaurByCodeDivideAndConquer(
    const DinosaurCollection& collection,
    const std::string& code,
    Dinosaur* result
);

// Presenta el menú de retos y utiliza las funciones anteriores.
void runRecursiveChallengesMenu(
    const DinosaurCollection& collection
);

#endif
