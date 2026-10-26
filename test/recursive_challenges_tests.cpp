#include "recursive_challenges.h"
#include "dinosaur.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>

/*
 * Construye un dinosaurio mínimo para las pruebas.
 * Complejidad: O(1), sin contar la copia de las cadenas.
 */
static Dinosaur makeDinosaur(
    const std::string& code,
    const std::string& name,
    double length,
    double weight
) {
    Dinosaur dinosaur;
    dinosaur.code = code;
    dinosaur.name = name;
    dinosaur.period = "Jurassic";
    dinosaur.diet = "Carnivore";
    dinosaur.lengthMeters = length;
    dinosaur.weightTons = weight;
    dinosaur.ageMillionsYears = 100.0;
    dinosaur.discoverySite = "Test site";
    return dinosaur;
}

/*
 * Prueba Fibonacci y sus límites.
 */
static void testFibonacci() {
    std::uint64_t result = 0;

    assert(calculateFibonacciBottomUp(0, &result));
    assert(result == 0);

    assert(calculateFibonacciBottomUp(1, &result));
    assert(result == 1);

    assert(calculateFibonacciBottomUp(6, &result));
    assert(result == 8);

    assert(calculateFibonacciBottomUp(10, &result));
    assert(result == 55);

    assert(calculateFibonacciBottomUp(93, &result));
    assert(result == 12200160415121876738ULL);

    assert(!calculateFibonacciBottomUp(94, &result));
    assert(!calculateFibonacciBottomUp(5, nullptr));
}

/*
 * Prueba nombres palíndromos y no palíndromos.
 */
static void testPalindrome() {
    assert(isDinosaurNamePalindrome("Ana"));
    assert(isDinosaurNamePalindrome("Anita lava la tina"));
    assert(isDinosaurNamePalindrome("oso"));
    assert(!isDinosaurNamePalindrome("Tyrannosaurus"));
    assert(!isDinosaurNamePalindrome("   "));
}

/*
 * Prueba peso total y búsqueda de un par de longitudes.
 */
static void testCollectionChallenges() {
    Dinosaur dinosaurs[3];

    dinosaurs[0] = makeDinosaur("DIN-003", "Rex", 4.0, 2.5);
    dinosaurs[1] = makeDinosaur("DIN-001", "Trike", 6.0, 3.0);
    dinosaurs[2] = makeDinosaur("DIN-002", "Raptor", 2.0, 0.5);

    DinosaurCollection collection;
    collection.items = dinosaurs;
    collection.count = 3;
    collection.capacity = 3;

    double totalWeight = 0.0;
    assert(calculateTotalWeightRecursive(collection, &totalWeight));
    assert(std::fabs(totalWeight - 6.0) < 1e-9);

    std::size_t first = 0;
    std::size_t second = 0;

    assert(findLengthPairBruteForce(
        collection, 10.0, &first, &second
    ));

    assert(first != second);
    assert(std::fabs(
        dinosaurs[first].lengthMeters
        + dinosaurs[second].lengthMeters - 10.0
    ) < 1e-9);

    assert(!findLengthPairBruteForce(
        collection, 100.0, &first, &second
    ));
}

/*
 * Prueba la formación recursiva de Pteranodons.
 */
static void testPteranodons() {
    std::uint64_t total = 0;

    assert(calculatePteranodonFormation(0, &total));
    assert(total == 0);

    assert(calculatePteranodonFormation(1, &total));
    assert(total == 1);

    assert(calculatePteranodonFormation(4, &total));
    assert(total == 10);

    assert(calculatePteranodonFormation(10000, &total));
    assert(total == 50005000);

    assert(!calculatePteranodonFormation(10001, &total));
    assert(!calculatePteranodonFormation(4, nullptr));
}

/*
 * Prueba búsqueda por código y confirma que la colección original
 * conserva su orden aunque no esté ordenada por código.
 */
static void testBinarySearch() {
    Dinosaur dinosaurs[3];

    dinosaurs[0] = makeDinosaur("DIN-003", "Rex", 4.0, 2.5);
    dinosaurs[1] = makeDinosaur("DIN-001", "Trike", 6.0, 3.0);
    dinosaurs[2] = makeDinosaur("DIN-002", "Raptor", 2.0, 0.5);

    DinosaurCollection collection;
    collection.items = dinosaurs;
    collection.count = 3;
    collection.capacity = 3;

    Dinosaur result;

    assert(findDinosaurByCodeDivideAndConquer(
        collection, "DIN-001", &result
    ));
    assert(result.name == "Trike");

    assert(findDinosaurByCodeDivideAndConquer(
        collection, "DIN-003", &result
    ));
    assert(result.name == "Rex");

    assert(!findDinosaurByCodeDivideAndConquer(
        collection, "DIN-999", &result
    ));

    // La función ordena una copia, no el arreglo original.
    assert(dinosaurs[0].code == "DIN-003");
    assert(dinosaurs[1].code == "DIN-001");
    assert(dinosaurs[2].code == "DIN-002");
}

int main() {
    testFibonacci();
    testPalindrome();
    testCollectionChallenges();
    testPteranodons();
    testBinarySearch();

    std::cout << "Todas las pruebas de retos pasaron.\n";
    return 0;
}
