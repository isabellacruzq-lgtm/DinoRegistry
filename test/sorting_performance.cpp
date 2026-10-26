#include "dinosaur_sorting.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

/*
 * Genera datos artificiales deterministas.
 * No utiliza archivos ni datos reales del proyecto.
 */
static void generateTestData(Dinosaur* items, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        Dinosaur dinosaur;

        dinosaur.code = "TEST-" + std::to_string(i);
        dinosaur.name =
            "Dinosaur_" + std::to_string((i * 7919) % count);

        dinosaur.period = "Jurassic";
        dinosaur.diet = "Carnivore";
        dinosaur.lengthMeters =
            static_cast<double>((i * 37) % 500) / 10.0;
        dinosaur.weightTons =
            static_cast<double>((i * 53) % 1000) / 10.0;
        dinosaur.ageMillionsYears =
            static_cast<double>((i * 29) % 200) + 1.0;
        dinosaur.discoverySite = "Test site";

        items[i] = dinosaur;
    }
}

/*
 * Verifica que el arreglo esté ordenado por nombre.
 */
static bool namesAreSorted(
    const Dinosaur* items,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        if (items[i - 1].name > items[i].name) {
            return false;
        }
    }

    return true;
}

/*
 * Verifica que el arreglo esté ordenado por longitud.
 */
static bool lengthsAreSorted(
    const Dinosaur* items,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        if (items[i - 1].lengthMeters >
            items[i].lengthMeters) {
            return false;
        }
    }

    return true;
}

/*
 * Verifica que el arreglo esté ordenado por peso.
 */
static bool weightsAreSorted(
    const Dinosaur* items,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        if (items[i - 1].weightTons >
            items[i].weightTons) {
            return false;
        }
    }

    return true;
}

/*
 * Verifica que el arreglo esté ordenado por edad.
 */
static bool agesAreSorted(
    const Dinosaur* items,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        if (items[i - 1].ageMillionsYears >
            items[i].ageMillionsYears) {
            return false;
        }
    }

    return true;
}

/*
 * Ejecuta un algoritmo sobre una copia de los datos.
 * Mide únicamente el tiempo del ordenamiento, no el de la copia.
 */
template <typename SortFunction, typename CheckFunction>
static void runBenchmark(
    const char* algorithm,
    const Dinosaur* original,
    std::size_t count,
    SortFunction sortFunction,
    CheckFunction checkFunction,
    bool showSwaps
) {
    Dinosaur* copy = new Dinosaur[count];

    for (std::size_t i = 0; i < count; ++i) {
        copy[i] = original[i];
    }

    SortStats stats;

    const std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    sortFunction(copy, count, stats);

    const std::chrono::steady_clock::time_point finish =
        std::chrono::steady_clock::now();

    const double milliseconds =
        std::chrono::duration<double, std::milli>(
            finish - start
        ).count();

    const bool valid = checkFunction(copy, count);

    std::cout
        << std::left << std::setw(20) << algorithm
        << std::right << std::setw(8) << count
        << std::setw(18) << stats.comparisons
        << std::setw(15) << std::fixed << std::setprecision(3)
        << milliseconds
        << std::setw(12) << (valid ? "OK" : "ERROR");

    if (showSwaps) {
        std::cout << std::setw(15) << stats.swaps;
    } else {
        std::cout << std::setw(15) << stats.movements;
    }

    std::cout << '\n';

    delete[] copy;
}

int main() {
    const std::size_t sizes[] = {100, 1000, 5000, 10000};
    const std::size_t numberOfSizes =
        sizeof(sizes) / sizeof(sizes[0]);

    std::cout
        << std::left << std::setw(20) << "Algoritmo"
        << std::right << std::setw(8) << "N"
        << std::setw(18) << "Comparaciones"
        << std::setw(15) << "Tiempo(ms)"
        << std::setw(12) << "Validacion"
        << std::setw(15) << "Interc./mov."
        << '\n';

    std::cout << std::string(88, '-') << '\n';

    for (std::size_t i = 0; i < numberOfSizes; ++i) {
        const std::size_t count = sizes[i];
        Dinosaur* original = new Dinosaur[count];

        generateTestData(original, count);

        runBenchmark(
            "Bubble Sort",
            original,
            count,
            bubbleSortByName,
            namesAreSorted,
            true
        );

        runBenchmark(
            "Selection Sort",
            original,
            count,
            selectionSortByName,
            namesAreSorted,
            true
        );

        runBenchmark(
            "Insertion Sort",
            original,
            count,
            insertionSortByLength,
            lengthsAreSorted,
            false
        );

        runBenchmark(
            "Merge Sort (peso)",
            original,
            count,
            mergeSortByWeight,
            weightsAreSorted,
            false
        );

        runBenchmark(
            "Merge Sort (edad)",
            original,
            count,
            mergeSortByAge,
            agesAreSorted,
            false
        );

        delete[] original;
    }

    return 0;
}