#include "dinosaur_console.h"
#include "dinosaur_management.h"
#include "dinosaur_search.h"
#include "file_persistence.h"
#include "dinosaur_sorting.h"
#include "excavation_map.h"
#include "recursive_challenges.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>
#include <cmath>
#include <sstream>

// Indica si el usuario cerró la entrada del programa.
static bool inputEnded = false;

/**
 * Lee una línea de texto y detecta el fin de entrada.
 * Parámetros: prompt, mensaje que se muestra al usuario.
 * Retorno: texto leído o cadena vacía si falla la lectura.
 * Complejidad: O(m), donde m es la longitud del texto.
 */
static std::string readText(const std::string& prompt) {
    std::string value;
    std::cout << prompt;

    if (!std::getline(std::cin, value)) {
        inputEnded = true;
        return "";
    }

    return value;
}



/**
 * Comprueba que un texto no esté vacío ni contenga solamente espacios.
 * Parámetros: value, texto que se comprobará.
 * Retorno: true si contiene algún carácter distinto de un espacio.
 * Complejidad: O(n), donde n es la longitud del texto.
 */
static bool hasContent(const std::string& value) {
    return value.find_first_not_of(" \t\r\n") != std::string::npos;
}

/**
 * Solicita un texto obligatorio y repite la pregunta si está vacío.
 * Parámetros: prompt, mensaje que se mostrará.
 * Retorno: texto ingresado o cadena vacía si termina la entrada.
 * Complejidad: depende de los intentos y la longitud del texto.
 */
static std::string readRequiredText(const std::string& prompt) {
    while (true) {
        std::string value = readText(prompt);
        if (inputEnded) return "";
        if (hasContent(value)) return value;
        std::cout << "El campo no puede estar vacío.\n";
    }
}

/**
 * Solicita un valor de una lista de opciones sin distinguir mayúsculas.
 * Parámetros: prompt, mensaje; validOptions, opciones permitidas;
 * optionCount, cantidad de opciones.
 * Retorno: opción válida o cadena vacía si termina la entrada.
 * Complejidad: depende de los intentos y de la cantidad de opciones.
 */
static std::string readChoiceText(
    const std::string& prompt,
    const std::string validOptions[],
    int optionCount
) {
    while (true) {
        std::string value = readRequiredText(prompt);
        if (inputEnded) return "";

        std::string normalized = value;
        for (std::size_t i = 0; i < normalized.length(); i++) {
            normalized[i] = static_cast<char>(
                std::tolower(static_cast<unsigned char>(normalized[i]))
            );
        }

        for (int i = 0; i < optionCount; i++) {
            std::string option = validOptions[i];
            for (std::size_t j = 0; j < option.length(); j++) {
                option[j] = static_cast<char>(
                    std::tolower(static_cast<unsigned char>(option[j]))
                );
            }
            if (normalized == option) return value;
        }

        std::cout << "Opción inválida. Intenta nuevamente.\n";
    }
}

/**
 * Lee un número finito no negativo y rechaza caracteres adicionales.
 * Parámetros: prompt, mensaje que se mostrará.
 * Retorno: número válido o cero si termina la entrada.
 * Complejidad: depende del número de intentos.
 */
static double readNumber(const std::string& prompt) {
    while (true) {
        std::string line = readText(prompt);
        if (inputEnded) return 0.0;

        std::istringstream input(line);
        double value;

        if (input >> value) {
            input >> std::ws;
            if (input.eof() && std::isfinite(value) && value >= 0.0) {
                return value;
            }
        }

        std::cout
            << "Entrada inválida. Escribe un número finito mayor o igual a cero.\n";
    }
}

/**
 * Lee una opción entera completa, sin aceptar texto adicional.
 * Parámetros: prompt, mensaje; value, variable donde se guarda la opción.
 * Retorno: true si se leyó un entero válido; false si terminó la entrada.
 * Complejidad: O(m), donde m es la longitud de la línea.
 */
static bool readIntegerOption(const std::string& prompt, int& value) {
    while (true) {
        std::string line = readText(prompt);
        if (inputEnded) return false;

        std::istringstream input(line);
        char extra;
        if ((input >> value) && !(input >> extra)) return true;

        std::cout << "Entrada inválida. Debes escribir un número entero.\n";
    }
}



/**

 * Lee los datos de un dinosaurio.

 * Parámetros:*

 *   dinosaur: estructura donde se guardan los datos.

 *   askCode: indica si se solicita un código.

 *   collection: colección usada para sugerir un código.

 * Retorno: true si se leyeron todos los datos; false si terminó la entrada.

 * Complejidad: depende de la longitud de los datos introducidos.

 */

static bool readDinosaur(
    Dinosaur& dinosaur,
    bool askCode,
    const DinosaurCollection* collection = nullptr
) {
    dinosaur.name = readRequiredText("Nombre: ");
    if (inputEnded) {
        return false;
    }

    if (askCode) {
        const std::string suggestedCode =
            collection != nullptr
                ? generateDinosaurCode(*collection, dinosaur.name)
                : "";

        std::cout << "Código sugerido: "
                  << (suggestedCode.empty() ? "No disponible" : suggestedCode)
                  << '\n';

        while (true) {
            const std::string code = readText(
                "Código (Enter para usar el sugerido): "
            );

            if (inputEnded) {
                return false;
            }

            if (code.empty()) {
                if (!suggestedCode.empty()) {
                    dinosaur.code = suggestedCode;
                    break;
                }

                std::cout
                    << "No se pudo generar un código. "
                    << "Escribe uno válido.\n";
                continue;
            }

            if (!isValidDinosaurCode(code)) {
                std::cout
                    << "Formato inválido. Usa letras mayúsculas, "
                    << "un guion y tres números; ejemplo: DIN-014.\n";
                continue;
            }

            dinosaur.code = code;
            break;
        }
    }

    const std::string validPeriods[] = {
        "Triassic", "Jurassic", "Cretaceous"
    };
    dinosaur.period = readChoiceText(
        "Período (Triassic/Jurassic/Cretaceous): ",
        validPeriods,
        3
    );

    if (inputEnded) {
        return false;
    }

    const std::string validDiets[] = {
        "Carnivore", "Herbivore", "Omnivore"
    };
    dinosaur.diet = readChoiceText(
        "Dieta (Carnivore/Herbivore/Omnivore): ",
        validDiets,
        3
    );

    if (inputEnded) {
        return false;
    }

    dinosaur.lengthMeters = readNumber("Longitud en metros: ");
    if (inputEnded) {
        return false;
    }

    dinosaur.weightTons = readNumber("Peso en toneladas: ");
    if (inputEnded) {
        return false;
    }

    dinosaur.ageMillionsYears = readNumber("Edad en millones de años: ");
    if (inputEnded) {
        return false;
    }

    dinosaur.discoverySite = readRequiredText("Lugar de descubrimiento: ");
    if (inputEnded) {
        return false;
    }

    return true;
}



/**

 * Muestra el perfil completo de un dinosaurio.

 * Parámetros: dinosaur, dinosaurio que se mostrará.

 * Retorno: ninguno.

 * Complejidad: O(1), sin contar la salida de los textos.

 */

static void printDinosaurProfile(const Dinosaur& dinosaur) {

    std::cout << "\n========== Perfil del dinosaurio ==========\n"

              << "Código: " << dinosaur.code << '\n'

              << "Nombre: " << dinosaur.name << '\n'

              << "Período: " << dinosaur.period << '\n'

              << "Dieta: " << dinosaur.diet << '\n'

              << "Longitud: " << dinosaur.lengthMeters << " metros\n"

              << "Peso: " << dinosaur.weightTons << " toneladas\n"

              << "Edad: " << dinosaur.ageMillionsYears

              << " millones de años\n"

              << "Lugar de descubrimiento: "

              << dinosaur.discoverySite << '\n'

              << "===========================================\n";

}



/**

 * Permite elegir un algoritmo de ordenamiento.

 * Ordena una copia para conservar la colección original.

 * Parámetros: collection, colección de dinosaurios.

 * Retorno: ninguno.

 * Complejidad: depende del algoritmo seleccionado.

 */

static void sortDinosaursFromConsole(
    const DinosaurCollection& collection
) {
    if (collection.count == 0) {
        std::cout << "La colección está vacía.\n";
        return;
    }

    std::cout
        << "\n--- Ordenamiento de dinosaurios ---\n"
        << "1. Ordenar por nombre (Bubble Sort)\n"
        << "2. Ordenar por nombre (Selection Sort)\n"
        << "3. Ordenar por longitud (Insertion Sort)\n"
        << "4. Ordenar por peso (Merge Sort)\n"
        << "5. Ordenar por edad (Merge Sort)\n";

    int option;
    if (!readIntegerOption("Selecciona una opción: ", option)) {
        return;
    }

    if (option < 1 || option > 5) {
        std::cout << "Opción inválida.\n";
        return;
    }

    Dinosaur* sorted = copyDinosaursForSorting(collection);
    SortStats stats;

    switch (option) {
        case 1:
            bubbleSortByName(sorted, collection.count, stats);
            std::cout << "\nAlgoritmo: Bubble Sort\n"
                      << "Tiempo: mejor O(n), peor O(n^2).\n"
                      << "Espacio auxiliar: O(1), más la copia.\n";
            break;

        case 2:
            selectionSortByName(sorted, collection.count, stats);
            std::cout << "\nAlgoritmo: Selection Sort\n"
                      << "Tiempo: O(n^2) en todos los casos.\n"
                      << "Espacio auxiliar: O(1), más la copia.\n";
            break;

        case 3:
            insertionSortByLength(sorted, collection.count, stats);
            std::cout << "\nAlgoritmo: Insertion Sort\n"
                      << "Tiempo: mejor O(n), peor O(n^2).\n"
                      << "Espacio auxiliar: O(1), más la copia.\n";
            break;

        case 4:
            mergeSortByWeight(sorted, collection.count, stats);
            std::cout << "\nAlgoritmo: Merge Sort por peso\n"
                      << "Tiempo: O(n log n) en todos los casos.\n"
                      << "Espacio auxiliar: O(n), más la copia.\n";
            break;

        case 5:
            mergeSortByAge(sorted, collection.count, stats);
            std::cout << "\nAlgoritmo: Merge Sort por edad\n"
                      << "Tiempo: O(n log n) en todos los casos.\n"
                      << "Espacio auxiliar: O(n), más la copia.\n";
            break;
    }

    std::cout << "\nResultados ordenados:\n";

    for (std::size_t i = 0; i < collection.count; ++i) {
        std::cout
            << i + 1 << ". "
            << sorted[i].name
            << " | Código: " << sorted[i].code
            << " | Longitud: " << sorted[i].lengthMeters
            << " m | Peso: " << sorted[i].weightTons
            << " t | Edad: " << sorted[i].ageMillionsYears
            << " millones de años\n";
    }

    std::cout << "\nComparaciones: " << stats.comparisons << '\n';

    if (option == 1 || option == 2) {
        std::cout << "Intercambios: " << stats.swaps << '\n';
    } else {
        std::cout << "Movimientos: " << stats.movements << '\n';
    }

    delete[] sorted;

    std::cout
        << "\nLa colección original permanece sin cambios.\n";
}



/**

 * Muestra todos los dinosaurios registrados.

 * Parámetros: collection, colección que se mostrará.

 * Retorno: ninguno.

 * Complejidad: O(n).

 */

static void listDinosaurs(const DinosaurCollection& collection) {
    if (collection.count == 0) {
        std::cout << "La colección está vacía.\n";
        return;
    }

    std::cout << "\nTotal de dinosaurios: "
              << collection.count << '\n';

    for (std::size_t i = 0; i < collection.count; ++i) {
        printDinosaurProfile(collection.items[i]);
    }
}



/**

 * Solicita los datos y agrega un dinosaurio.

 * Parámetros: collection, colección que se modificará.

 * Retorno: ninguno.

 * Complejidad: depende de la búsqueda y del crecimiento de la colección.

 */

static void addDinosaurFromConsole(DinosaurCollection& collection) {
    Dinosaur dinosaur;

    if (!readDinosaur(dinosaur, true, &collection)) {
        return;
    }

    if (addDinosaur(collection, dinosaur)) {
        std::cout << "Dinosaurio agregado correctamente.\n";
    } else {
        std::cout
            << "No se agregó. Revisa que el código no esté vacío "
            << "ni repetido y que haya memoria disponible.\n";
    }
}

/**

 * Edita un dinosaurio conservando su código original.

 * Parámetros: collection, colección que se modificará.

 * Retorno: ninguno.

 * Complejidad: depende de la búsqueda y de la actualización.

 */

static void editDinosaurFromConsole(DinosaurCollection& collection) {
    const std::string code = readText(
        "Código del dinosaurio que deseas editar: "
    );

    if (inputEnded) {
        return;
    }

    Dinosaur dinosaur;

    if (!getDinosaurByCode(collection, code, dinosaur)) {
        std::cout << "No se encontró ese código.\n";
        return;
    }

    std::cout
        << "Introduce los nuevos datos. "
        << "El código original se conservará.\n";

    if (!readDinosaur(dinosaur, false)) {
        return;
    }

    if (editDinosaur(collection, code, dinosaur)) {
        std::cout << "Dinosaurio actualizado correctamente.\n";
    } else {
        std::cout << "No fue posible actualizar el dinosaurio.\n";
    }
}
/**
 * Elimina un dinosaurio por código.
 * Parámetros: collection, colección que se modificará.
 * Retorno: ninguno.
 * Complejidad: depende de la búsqueda en la colección.
 */

static void deleteDinosaurFromConsole(
    DinosaurCollection& collection
) {
    const std::string code = readText(
        "Código del dinosaurio que deseas eliminar: "
    );

    if (inputEnded) {
        return;
    }

    if (deleteDinosaur(collection, code)) {
        std::cout << "Dinosaurio eliminado correctamente.\n";
    } else {
        std::cout << "No se encontró ese código.\n";
    }

}

/**
 * Muestra el perfil de un dinosaurio buscado por código.
 * Parámetros: collection, colección donde se buscará.
 * Retorno: ninguno.
 * Complejidad: depende de la búsqueda.
 */

static void showDinosaurFromConsole(
    const DinosaurCollection& collection
) {
    const std::string code = readText(
        "Código del dinosaurio que deseas consultar: "
    );

    if (inputEnded) {
        return;
    }

    Dinosaur dinosaur;
    if (getDinosaurByCode(collection, code, dinosaur)) {
        printDinosaurProfile(dinosaur);
    } else {
        std::cout << "No se encontró ese código.\n";
    }
}

/**
 * Busca dinosaurios por nombre o fragmento del nombre.
 * Parámetros: collection, colección donde se buscará.
 * Retorno: ninguno.
 * Complejidad aproximada: O(n * m), según la búsqueda implementada.
 */

static void searchDinosaursByName(
    const DinosaurCollection& collection
) {
    const std::string query = readText(
        "Nombre o parte del nombre que deseas buscar: "
    );

    if (inputEnded) {
        return;
    }

    if (query.empty()) {
        std::cout << "La búsqueda no puede estar vacía.\n";
        return;
    }

    int* results = new int[
        collection.count == 0 ? 1 : collection.count
    ];

    const std::size_t matches = findDinosaursByName(
        collection,
        query,
        results,
        collection.count
    );

    if (matches == 0) {
        std::cout << "No se encontraron coincidencias.\n";
    } else {
        std::cout << "\nCoincidencias encontradas: "
                  << matches << '\n';

        const std::size_t displayed =
            matches < collection.count ? matches : collection.count;

        for (std::size_t i = 0; i < displayed; ++i) {
            printDinosaurProfile(collection.items[results[i]]);
        }
    }

    delete[] results;
}

/**
 * Cuenta apariciones de una letra o texto en todos los nombres.
 * Parámetros: collection, colección cuyos nombres se analizarán.
 * Retorno: ninguno.
 * Complejidad: depende de la cantidad de nombres y sus longitudes.
 */

static void countTextInNames(
    const DinosaurCollection& collection
) {
    const std::string text = readText(
        "Letra o texto que deseas contar en los nombres: "
    );

    if (inputEnded) {
        return;
    }

    if (text.empty()) {
        std::cout << "El texto no puede estar vacío.\n";
        return;
    }

    std::cout << "Apariciones encontradas: "
              << countOccurrencesInNames(collection, text)
              << '\n';

}

/**
 * Estima grupos vocálicos en un nombre.
 * Parámetros: ninguno; el nombre se solicita por consola.
 * Retorno: ninguno.
 * Complejidad: depende de la longitud del nombre.
 */

static void countNameVowelGroups() {
    const std::string name = readText(
        "Nombre que deseas analizar: "
    );

    if (inputEnded) {
        return;
    }
    std::cout << "Grupos vocálicos aproximados: "
              << countSyllableGroups(name) << '\n';

}

/**
 * Ejecuta el menú principal de DinoRegistry.
 * Paráetros: collection, colección que administrará el menú.
 * Retorno: ninguno.
 * Complejidad: depende de las opciones elegidas.
 */

void runDinosaurMenu(DinosaurCollection& collection) {
    bool running = true;

    while (running) {

        std::cout
            << "\n========== DinoRegistry ==========\n"
            << "1. Agregar dinosaurio\n"
            << "2. Editar dinosaurio\n"
            << "3. Eliminar dinosaurio\n"
            << "4. Listar dinosaurios\n"
            << "5. Mostrar perfil por código\n"
            << "6. Buscar dinosaurio por nombre\n"
            << "7. Contar letras o texto en nombres\n"
            << "8. Estimar grupos vocálicos de un nombre\n"
            << "9. Guardar colección en archivo\n"
            << "10. Ordenar dinosaurios\n"
            << "11. Analizar mapa de excavación\n"
            << "12. Retos de visitantes\n"
            << "0. Salir\n";

        int option;
        if (!readIntegerOption("Selecciona una opción: ", option)) {
            break;
        }

        switch (option) {
            case 1:
                addDinosaurFromConsole(collection);
                break;

            case 2:
                editDinosaurFromConsole(collection);
                break;

            case 3:
                deleteDinosaurFromConsole(collection);
                break;

            case 4:
                listDinosaurs(collection);
                break;

            case 5:
                showDinosaurFromConsole(collection);
                break;

            case 6:
                searchDinosaursByName(collection);
                break;

            case 7:
                countTextInNames(collection);
                break;

            case 8:
                countNameVowelGroups();
                break;

            case 9:
                if (saveDinosaursToFile(collection, "dinosaurs.txt")) {
                    generateReport(collection, "report.txt");
                }
                break;

            case 10:
                sortDinosaursFromConsole(collection);
                break;

            case 11:
                runExcavationMapMenu("excavation.txt");
                break;

            case 12:
                runRecursiveChallengesMenu(collection);
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout
                    << "Opción no válida. Intenta de nuevo.\n";
                break;
        }

        // Si una opción detectó el fin de entrada, termina el menú.
        if (inputEnded) {
            running = false;
        }

    }

}