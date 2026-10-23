#include "dinosaur_console.h"
#include "dinosaur_management.h"
#include "file_persistence.h"

#include <iostream>
#include <limits>
#include <string>

/*
 * Lee una línea de texto.
 * Parámetros: prompt, mensaje que se mostrará.
 * Retorno: texto introducido.
 * Complejidad: O(m), donde m es la longitud de la entrada.
 */
static std::string readText(const std::string& prompt) {
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}

/*
 * Lee un número no negativo y vuelve a preguntar si la entrada no es válida.
 * Parámetros: prompt, mensaje que se mostrará.
 * Retorno: número introducido.
 * Complejidad: depende del número de intentos del usuario.
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

        std::cout << "Entrada inválida. Usa un número mayor o igual a cero.\n";
    }
}

/*
 * Lee los datos de un dinosaurio.
 * Parámetros: dinosaur, estructura donde se guardan los datos;
 * askCode, indica si se debe solicitar el código.
 * Retorno: ninguno.
 * Complejidad: depende de la longitud de los datos introducidos.
 */
static void readDinosaur(Dinosaur& dinosaur, bool askCode) {
    if (askCode) {
        dinosaur.code = readText("Código (ej. DIN-014): ");
    }

    dinosaur.name = readText("Nombre: ");
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
    dinosaur.discoverySite = readText("Lugar de descubrimiento: ");
}

/*
 * Muestra el perfil completo de un dinosaurio.
 * Parámetros: dinosaur, registro que se mostrará.
 * Retorno: ninguno.
 * Complejidad: O(1) respecto al número de campos.
 */
static void printDinosaurProfile(const Dinosaur& dinosaur) {
    std::cout << "\n"
              << "============================================\n"
              << "          PERFIL DEL DINOSAURIO\n"
              << "============================================\n"
              << "Código:                  " << dinosaur.code << '\n'
              << "Nombre:                  " << dinosaur.name << '\n'
              << "Período:                 " << dinosaur.period << '\n'
              << "Dieta:                   " << dinosaur.diet << '\n'
              << "Longitud (metros):       " << dinosaur.lengthMeters << '\n'
              << "Peso (toneladas):        " << dinosaur.weightTons << '\n'
              << "Edad (millones de años): "
              << dinosaur.ageMillionsYears << '\n'
              << "Lugar de descubrimiento: "
              << dinosaur.discoverySite << '\n'
              << "============================================\n";
}

/*
 * Muestra todos los dinosaurios registrados.
 * Parámetros: collection, colección que se mostrará.
 * Retorno: ninguno.
 * Complejidad: O(n), donde n es la cantidad de registros.
 */
static void listDinosaurs(const DinosaurCollection& collection) {
    if (collection.count == 0) {
        std::cout << "La colección está vacía.\n";
        return;
    }

    std::cout << "\nTotal de dinosaurios: " << collection.count << '\n';

    for (std::size_t i = 0; i < collection.count; ++i) {
        printDinosaurProfile(collection.items[i]);
    }
}

/*
 * Solicita los datos y llama a la función que agrega el dinosaurio.
 * Parámetros: collection, colección que se modificará.
 * Retorno: ninguno.
 * Complejidad: O(n) por la búsqueda del código y posible ampliación.
 */
static void addDinosaurFromConsole(DinosaurCollection& collection) {
    Dinosaur dinosaur;
    readDinosaur(dinosaur, true);

    if (addDinosaur(collection, dinosaur)) {
        std::cout << "Dinosaurio agregado correctamente.\n";
    } else {
        std::cout
            << "No se agregó. Revisa que el código no esté vacío "
            << "ni repetido y que haya memoria disponible.\n";
    }
}

/*
 * Solicita un código, permite cambiar los datos y conserva el código original.
 * Parámetros: collection, colección que se modificará.
 * Retorno: ninguno.
 * Complejidad: O(n).
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
 * Solicita un código y elimina el registro correspondiente.
 * Parámetros: collection, colección que se modificará.
 * Retorno: ninguno.
 * Complejidad: O(n).
 */
static void deleteDinosaurFromConsole(DinosaurCollection& collection) {
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
 * Busca y muestra el perfil de un dinosaurio por código.
 * Parámetros: collection, colección consultada.
 * Retorno: ninguno.
 * Complejidad: O(n).
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
 * Muestra el menú y procesa las opciones hasta que el usuario sale.
 * Parámetros: collection, colección que administrará el menú.
 * Retorno: ninguno.
 * Complejidad: depende de las operaciones seleccionadas.
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
            << "6. Guardar coleccion en archivo\n"
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

            std::cout << "Entrada inválida. Debes escribir un número.\n";
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
                if (saveDinosaursToFile(collection, "dinosaurs.txt")) {
                    generateReport(collection, "report.txt");
                }
                break;

            case 0:
                running = false;
                break;

            default:
                std::cout << "Opción no válida. Intenta de nuevo.\n";
                break;
        }
    }
}
