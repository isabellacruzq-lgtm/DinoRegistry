#include "dinosaur_console.h"
#include "dinosaur_management.h"
#include "dinosaur_search.h"
#include "file_persistence.h"
#include "dinosaur_sorting.h"
#include "excavation_map.h"

#include <iostream>
#include <limits>
#include <string>

/*
 * Lee una línea de texto.
 * Complejidad: O(m), donde m es la longitud de la entrada.
 */
static std::string readText(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

/*
 * Lee un número no negativo.
 * Complejidad: depende del número de intentos.
 */
static double readNumber(const std::string& prompt) {
    double value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            if (value >= 0.0) {
                return value;
            }
        } else {
            if (std::cin.eof()) {
                return 0.0;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );
        }

        std::cout
            << "Entrada inválida. Usa un número mayor o igual a cero.\n";
    }
}

/*
 * Lee los datos de un dinosaurio.
 * Si askCode es true, solicita o genera un código.
 */
static void readDinosaur(
    Dinosaur& dinosaur,
    bool askCode,
    const DinosaurCollection* collection = nullptr
) {
    dinosaur.name = readText("Nombre: ");

    if (askCode) {
        const std::string suggestedCode =
            collection != nullptr
                ? generateDinosaurCode(*collection, dinosaur.name)
                : "";

        std::cout << "Código sugerido: "
                  << (suggestedCode.empty()
                          ? "No disponible"
                          : suggestedCode)
                  << '\n';

        while (true) {
            const std::string code = readText(
                "Código (Enter para usar el sugerido): "
            );

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

    dinosaur.period = readText(
        "Período (Triassic/Jurassic/Cretaceous): "
    );
    dinosaur.diet = readText(
        "Dieta (Carnivore/Herbivore/Omnivore): "
    );
    dinosaur.lengthMeters = readNumber("Longitud en metros: ");
    dinosaur.weightTons = readNumber("Peso en toneladas: ");
    dinosaur.ageMillionsYears = readNumber(
        "Edad en millones de años: "
    );
    dinosaur.discoverySite = readText(
        "Lugar de descubrimiento: "
    );
}

/*
 * Muestra el perfil completo de un dinosaurio.
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

/*
 * Permite elegir un criterio y un algoritmo permitido.
 * Ordena una copia, sin modificar la colección original.
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
        << "5. Ordenar por edad (Merge Sort)\n"
        << "Selecciona una opción: ";

    int option;

    if (!(std::cin >> option)) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        std::cout << "Opción inválida.\n";
        return;
    }

    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(), '\n'
    );

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


/*
 * Muestra todos los dinosaurios registrados.
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

/*
 * Agrega un dinosaurio nuevo.
 */
static void addDinosaurFromConsole(DinosaurCollection& collection) {
    Dinosaur dinosaur;
    readDinosaur(dinosaur, true, &collection);

    if (addDinosaur(collection, dinosaur)) {
        std::cout << "Dinosaurio agregado correctamente.\n";
    } else {
        std::cout
            << "No se agregó. Revisa que el código no esté vacío "
            << "ni repetido y que haya memoria disponible.\n";
    }
}

/*
 * Edita un dinosaurio conservando su código original.
 */
static void editDinosaurFromConsole(DinosaurCollection& collection) {
    const std::string code = readText(
        "Código del dinosaurio que deseas editar: "
    );

    Dinosaur dinosaur;

    if (!getDinosaurByCode(collection, code, dinosaur)) {
        std::cout << "No se encontró ese código.\n";
        return;
    }

    std::cout
        << "Introduce los nuevos datos. "
        << "El código original se conservará.\n";

    readDinosaur(dinosaur, false);

    if (editDinosaur(collection, code, dinosaur)) {
        std::cout << "Dinosaurio actualizado correctamente.\n";
    } else {
        std::cout << "No fue posible actualizar el dinosaurio.\n";
    }
}

/*
 * Elimina un dinosaurio por código.
 */
static void deleteDinosaurFromConsole(
    DinosaurCollection& collection
) {
    const std::string code = readText(
        "Código del dinosaurio que deseas eliminar: "
    );

    if (deleteDinosaur(collection, code)) {
        std::cout << "Dinosaurio eliminado correctamente.\n";
    } else {
        std::cout << "No se encontró ese código.\n";
    }
}

/*
 * Muestra el perfil de un dinosaurio buscado por código.
 */
static void showDinosaurFromConsole(
    const DinosaurCollection& collection
) {
    const std::string code = readText(
        "Código del dinosaurio que deseas consultar: "
    );

    Dinosaur dinosaur;

    if (getDinosaurByCode(collection, code, dinosaur)) {
        printDinosaurProfile(dinosaur);
    } else {
        std::cout << "No se encontró ese código.\n";
    }
}

/*
 * Busca dinosaurios por nombre o fragmento del nombre.
 * Complejidad aproximada: O(n * m).
 */
static void searchDinosaursByName(
    const DinosaurCollection& collection
) {
    const std::string query = readText(
        "Nombre o parte del nombre que deseas buscar: "
    );

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
            printDinosaurProfile(
                collection.items[results[i]]
            );
        }
    }

    delete[] results;
}

/*
 * Cuenta apariciones de una letra o texto en todos los nombres.
 */
static void countTextInNames(
    const DinosaurCollection& collection
) {
    const std::string text = readText(
        "Letra o texto que deseas contar en los nombres: "
    );

    if (text.empty()) {
        std::cout << "El texto no puede estar vacío.\n";
        return;
    }

    std::cout << "Apariciones encontradas: "
              << countOccurrencesInNames(collection, text)
              << '\n';
}

/*
 * Estima grupos vocálicos en un nombre.
 * Es una aproximación, no un contador lingüístico exacto de sílabas.
 */
static void countNameVowelGroups() {
    const std::string name = readText(
        "Nombre que deseas analizar: "
    );

    std::cout << "Grupos vocálicos aproximados: "
              << countSyllableGroups(name) << '\n';
}

/*
 * Menú principal de DinoRegistry.
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
            << "0. Salir\n"
            << "Selecciona una opción: ";

        int option;

        if (!(std::cin >> option)) {
            if (std::cin.eof()) {
                break;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n'
            );

            std::cout
                << "Entrada inválida. Debes escribir un número.\n";
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );

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

            case 0:
                running = false;
                break;

            default:
                std::cout
                    << "Opción no válida. Intenta de nuevo.\n";
                break;
        }
    }
}
