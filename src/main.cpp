#include "dinosaur_collection.h"
#include "dinosaur_console.h"
#include "file_persistence.h"

#include <iostream>

int main() {
    DinosaurCollection collection;
    initializeCollection(collection);

    // Carga los datos antes de mostrar el menu.
    loadDinosaursFromFile(collection, "dinosaurs.txt");

    // Muestra el mapa si el archivo esta disponible.
    readExcavationMap("excavation.txt");

    // El menu permite gestionar la coleccion y guardar manualmente.
    runDinosaurMenu(collection);

    // Guarda y genera el reporte al salir.
    const bool saved =
        saveDinosaursToFile(collection, "dinosaurs.txt");

    const bool reported =
        generateReport(collection, "report.txt");

    if (!saved || !reported) {
        std::cerr
            << "Aviso: una o mas operaciones de archivo fallaron. "
            << "Revisa los mensajes anteriores.\n";
    }

    freeCollection(collection);

    std::cout << "Memoria liberada. Hasta luego.\n";
    return 0;
}
