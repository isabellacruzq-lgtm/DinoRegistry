#include "dinosaur_collection.h"

// Inicializa una colección vacía y deja listo su arreglo dinámico.
void initializeCollection(DinosaurCollection& collection) {
    // Todavía no hay elementos asignados, por eso el arreglo apunta a null.
    collection.items = nullptr;
    // La colección empieza sin elementos almacenados.
    collection.count = 0;
    // Tampoco tiene capacidad reservada.
    collection.capacity = 0;
}

// Libera la memoria usada por la colección y la devuelve a un estado vacío.
void freeCollection(DinosaurCollection& collection) {
    // Libera el arreglo de dinosaurios creado dinámicamente.
    delete[] collection.items;
    // Evita que el puntero siga haciendo referencia a memoria liberada.
    collection.items = nullptr;
    // Restablece la cantidad de elementos.
    collection.count = 0;
    // Restablece la capacidad reservada.
    collection.capacity = 0;
}
