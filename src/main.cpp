#include "dinosaur_collection.h"
#include "dinosaur_console.h"

#include <iostream>

/*
 * Inicializa la colección, ejecuta el menú y libera la memoria al salir.
 * Parámetros: ninguno.
 * Retorno: 0 si el programa termina correctamente.
 * Complejidad: depende de las operaciones seleccionadas en el menú.
 */
int main() {
    DinosaurCollection collection;

    initializeCollection(collection);

    runDinosaurMenu(collection);

    freeCollection(collection);

    std::cout << "Memoria liberada. Hasta luego.\n";

    return 0;
}