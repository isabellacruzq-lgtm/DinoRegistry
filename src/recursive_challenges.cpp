#include "recursive_challenges.h"
#include "dinosaur.h"

#include <cmath>
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

/*
 * Normaliza un nombre: elimina espacios y convierte a minúsculas.
 * Parámetro: nombre original.
 * Retorno: nombre normalizado.
 * Complejidad: O(m) en tiempo y espacio.
 */
static std::string normalizeName(const std::string& name) {
    std::string normalized;

    for (std::size_t i = 0; i < name.size(); ++i) {
        const unsigned char character =
            static_cast<unsigned char>(name[i]);

        if (!std::isspace(character)) {
            normalized += static_cast<char>(
                std::tolower(character)
            );
        }
    }

    return normalized;
}

/*
 * Comprueba un palíndromo comparando extremos recursivamente.
 * Parámetros: texto y límites izquierdo y derecho.
 * Retorno: true si los caracteres coinciden.
 * Complejidad: O(m) en tiempo y O(m) en pila.
 */
static bool palindromeRecursive(
    const std::string& text,
    std::size_t left,
    std::size_t right
) {
    if (left >= right) {
        return true;
    }

    if (text[left] != text[right]) {
        return false;
    }

    return palindromeRecursive(text, left + 1, right - 1);
}

/*
 * Suma los pesos desde el índice indicado hasta el final.
 * Caso base: índice igual al número de dinosaurios.
 * Complejidad: O(n) en tiempo y O(n) en pila.
 */
static double sumWeightsRecursive(
    const DinosaurCollection& collection,
    std::size_t index
) {
    if (index >= collection.count) {
        return 0.0;
    }

    return collection.items[index].weightTons
        + sumWeightsRecursive(collection, index + 1);
}

/*
 * Calcula 1 + 2 + ... + rows mediante recursión.
 * Caso base: cero filas.
 * Complejidad: O(n) en tiempo y O(n) en pila.
 */
static std::uint64_t pteranodonRecursive(unsigned int rows) {
    if (rows == 0) {
        return 0;
    }

    return static_cast<std::uint64_t>(rows)
        + pteranodonRecursive(rows - 1);
}

/*
 * Comprueba si los códigos están ordenados ascendentemente.
 * Parámetro: arreglo y cantidad de elementos.
 * Retorno: true si están ordenados.
 * Complejidad: O(n) en tiempo y O(1) en espacio.
 */
static bool codesAreSorted(
    const Dinosaur* dinosaurs,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        if (dinosaurs[i - 1].code > dinosaurs[i].code) {
            return false;
        }
    }

    return true;
}

/*
 * Ordena una copia de dinosaurios por código mediante inserción.
 * Parámetros: arreglo y cantidad.
 * Retorno: ninguno.
 * Complejidad: O(n^2) en tiempo y O(1) en espacio auxiliar.
 */
static void insertionSortByCode(
    Dinosaur* dinosaurs,
    std::size_t count
) {
    for (std::size_t i = 1; i < count; ++i) {
        Dinosaur current = dinosaurs[i];
        std::size_t j = i;

        while (j > 0 &&
               dinosaurs[j - 1].code > current.code) {
            dinosaurs[j] = dinosaurs[j - 1];
            --j;
        }

        dinosaurs[j] = current;
    }
}

/*
 * Busca recursivamente un código en un arreglo ordenado.
 * Caso base: el intervalo queda vacío.
 * Complejidad: O(log n) en tiempo y O(log n) en pila.
 */
static bool binarySearchRecursive(
    const Dinosaur* dinosaurs,
    std::size_t left,
    std::size_t right,
    const std::string& code,
    Dinosaur* result
) {
    if (left >= right) {
        return false;
    }

    const std::size_t middle = left + (right - left) / 2;

    if (dinosaurs[middle].code == code) {
        *result = dinosaurs[middle];
        return true;
    }

    if (code < dinosaurs[middle].code) {
        return binarySearchRecursive(
            dinosaurs, left, middle, code, result
        );
    }

    return binarySearchRecursive(
        dinosaurs, middle + 1, right, code, result
    );
}

/*
 * Calcula Fibonacci bottom-up sin recursión.
 * Casos base: F(0)=0 y F(1)=1.
 * Parámetros: n y puntero donde se guarda el resultado.
 * Retorno: false si la entrada no es válida.
 * Complejidad: O(n) en tiempo y O(1) en espacio.
 */
bool calculateFibonacciBottomUp(
    unsigned int n,
    std::uint64_t* result
) {
    if (result == nullptr || n > MAX_FIBONACCI_N) {
        return false;
    }

    if (n == 0) {
        *result = 0;
        return true;
    }

    std::uint64_t previous = 0;
    std::uint64_t current = 1;

    for (unsigned int i = 2; i <= n; ++i) {
        const std::uint64_t next = previous + current;
        previous = current;
        current = next;
    }

    *result = current;
    return true;
}

/*
 * Determina si un nombre normalizado se lee igual al revés.
 * Rechaza nombres vacíos o compuestos solo por espacios.
 * Complejidad: O(m) en tiempo y espacio.
 */
bool isDinosaurNamePalindrome(const std::string& name) {
    const std::string normalized = normalizeName(name);

    if (normalized.empty()) {
        return false;
    }

    return palindromeRecursive(
        normalized, 0, normalized.size() - 1
    );
}

/*
 * Calcula recursivamente el peso de todos los dinosaurios.
 * Parámetros: colección y puntero de salida.
 * Retorno: false si la colección no es válida o supera el límite.
 * Complejidad: O(n) en tiempo y O(n) en pila.
 */
bool calculateTotalWeightRecursive(
    const DinosaurCollection& collection,
    double* totalWeight
) {
    if (totalWeight == nullptr ||
        (collection.count > 0 && collection.items == nullptr) ||
        collection.count > MAX_RECURSIVE_ITEMS) {
        return false;
    }

    *totalWeight = sumWeightsRecursive(collection, 0);
    return true;
}

/*
 * Busca por fuerza bruta dos dinosaurios distintos que sumen
 * una longitud objetivo. Se permite una tolerancia de 1e-9
 * para compensar pequeñas diferencias de punto flotante.
 * Complejidad: O(n^2) en tiempo y O(1) en espacio.
 */
bool findLengthPairBruteForce(
    const DinosaurCollection& collection,
    double targetLength,
    std::size_t* firstIndex,
    std::size_t* secondIndex
) {
    if (firstIndex == nullptr || secondIndex == nullptr ||
        !std::isfinite(targetLength) ||
        (collection.count > 0 && collection.items == nullptr)) {
        return false;
    }

    for (std::size_t i = 0; i < collection.count; ++i) {
        for (std::size_t j = i + 1; j < collection.count; ++j) {
            const double sum =
                collection.items[i].lengthMeters
                + collection.items[j].lengthMeters;

            if (std::fabs(sum - targetLength) <= 1e-9) {
                *firstIndex = i;
                *secondIndex = j;
                return true;
            }
        }
    }

    return false;
}

/*
 * Calcula la cantidad total de Pteranodons en n filas.
 * Parámetros: cantidad de filas y puntero de salida.
 * Retorno: false si n excede el límite o el puntero es nulo.
 * Complejidad: O(n) en tiempo y O(n) en pila.
 */
bool calculatePteranodonFormation(
    unsigned int rows,
    std::uint64_t* total
) {
    if (total == nullptr || rows > MAX_RECURSIVE_ITEMS) {
        return false;
    }

    *total = pteranodonRecursive(rows);
    return true;
}

/*
 * Busca un código mediante divide y vencerás.
 * Se ordena una copia para garantizar el requisito de búsqueda
 * binaria y mantener intacta la colección original.
 * Complejidad: O(n^2) de preparación y O(log n) de búsqueda.
 */
bool findDinosaurByCodeDivideAndConquer(
    const DinosaurCollection& collection,
    const std::string& code,
    Dinosaur* result
) {
    if (result == nullptr || code.empty() ||
        (collection.count > 0 && collection.items == nullptr)) {
        return false;
    }

    if (collection.count == 0) {
        return false;
    }

    Dinosaur* sorted = new Dinosaur[collection.count];

    for (std::size_t i = 0; i < collection.count; ++i) {
        sorted[i] = collection.items[i];
    }

    // La copia se ordena aunque la colección original no lo esté.
    insertionSortByCode(sorted, collection.count);

    // Verificación explícita antes de usar la búsqueda binaria.
    if (!codesAreSorted(sorted, collection.count)) {
        delete[] sorted;
        return false;
    }

    const bool found = binarySearchRecursive(
        sorted, 0, collection.count, code, result
    );

    delete[] sorted;
    return found;
}

/*
 * Lee un entero sin aceptar texto inválido.
 * Complejidad: depende del número de intentos.
 */
static bool readUnsignedValue(
    const std::string& prompt,
    unsigned int& value
) {
    std::cout << prompt;

    if (!(std::cin >> value)) {
        if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
        }

        std::cout << "Entrada inválida.\n";
        return false;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n'
    );

    return true;
}

/*
 * Presenta los seis retos de visitantes.
 * Complejidad: depende de los retos seleccionados.
 */
void runRecursiveChallengesMenu(
    const DinosaurCollection& collection
) {
    bool running = true;

    while (running) {
        std::cout
            << "\n===== Retos de visitantes =====\n"
            << "1. Fibonacci bottom-up\n"
            << "2. Comprobar nombre palíndromo\n"
            << "3. Peso total recursivo\n"
            << "4. Par de longitudes por fuerza bruta\n"
            << "5. Formación de Pteranodons\n"
            << "6. Buscar código por divide y vencerás\n"
            << "0. Volver al menú principal\n"
            << "Opción: ";

        unsigned int option;

        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                return;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
            std::cout << "Opción inválida.\n";
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

        if (option == 0) {
            running = false;
        } else if (option == 1) {
            unsigned int n;
            std::uint64_t result = 0;

            if (readUnsignedValue("Generación n (0 a 93): ", n)) {
                if (calculateFibonacciBottomUp(n, &result)) {
                    std::cout << "Fibonacci(" << n << ") = "
                              << result << '\n';
                } else {
                    std::cout << "n debe estar entre 0 y 93.\n";
                }
            }
        } else if (option == 2) {
            std::string name;

            std::cout << "Nombre del dinosaurio: ";
            std::getline(std::cin, name);

            if (isDinosaurNamePalindrome(name)) {
                std::cout << "El nombre es palíndromo.\n";
            } else {
                std::cout << "El nombre no es palíndromo "
                          << "o está vacío.\n";
            }
        } else if (option == 3) {
            double total = 0.0;

            if (calculateTotalWeightRecursive(collection, &total)) {
                std::cout << "Peso total: " << total
                          << " toneladas.\n";
            } else {
                std::cout << "No se puede calcular: colección "
                          << "inválida o demasiado grande.\n";
            }
        } else if (option == 4) {
            double target;

            std::cout << "Longitud objetivo en metros: ";

            if (!(std::cin >> target)) {
                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n'
                );
                std::cout << "Longitud inválida.\n";
                continue;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            std::size_t first = 0;
            std::size_t second = 0;

            if (findLengthPairBruteForce(
                    collection, target, &first, &second)) {
                std::cout << collection.items[first].name
                          << " (" << collection.items[first].lengthMeters
                          << " m) + "
                          << collection.items[second].name
                          << " (" << collection.items[second].lengthMeters
                          << " m) = " << target << " m\n";
            } else {
                std::cout << "No se encontró un par de dinosaurios "
                          << "con esa longitud total.\n";
            }
        } else if (option == 5) {
            unsigned int rows;
            std::uint64_t total = 0;

            if (readUnsignedValue(
                    "Número de filas (0 a 10000): ", rows)) {
                if (calculatePteranodonFormation(rows, &total)) {
                    std::cout << "Total de Pteranodons: "
                              << total << '\n';
                } else {
                    std::cout << "El número de filas debe estar "
                              << "entre 0 y 10000.\n";
                }
            }
        } else if (option == 6) {
            std::string code;
            Dinosaur result;

            std::cout << "Código que deseas buscar: ";
            std::getline(std::cin, code);

            if (findDinosaurByCodeDivideAndConquer(
                    collection, code, &result)) {
                std::cout << "Dinosaurio encontrado: "
                          << result.code << " - "
                          << result.name << '\n';
            } else {
                std::cout << "No se encontró el código.\n";
            }
        } else {
            std::cout << "Opción no válida.\n";
        }
    }
}
