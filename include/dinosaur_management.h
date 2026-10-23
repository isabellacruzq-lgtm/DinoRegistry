#ifndef DINOSAUR_MANAGEMENT_H
#define DINOSAUR_MANAGEMENT_H

#include "dinosaur_collection.h"
#include <string>

/*
 * Busca un dinosaurio por su código.
 * Parámetros: collection, colección consultada; code, código buscado.
 * Retorno: índice encontrado o -1 si no existe.
 * Complejidad: O(n * m), donde n es el número de registros y m
 * la longitud del código.
 */
int findDinosaurByCode(
    const DinosaurCollection& collection,
    const std::string& code
);

/*
 * Agrega un dinosaurio si el código no está repetido.
 * Parámetros: collection, colección que se modifica; dinosaur, registro nuevo.
 * Retorno: true si se agregó; false si el código está vacío, repetido
 * o no se pudo reservar memoria.
 * Complejidad: O(n) por la búsqueda y la posible ampliación.
 */
bool addDinosaur(
    DinosaurCollection& collection,
    const Dinosaur& dinosaur
);

/*
 * Edita los datos de un dinosaurio existente.
 * Parámetros: collection, colección que se modifica; code, código original;
 * updatedDinosaur, datos nuevos.
 * Retorno: true si se editó; false si no existe el código.
 * Complejidad: O(n).
 */
bool editDinosaur(
    DinosaurCollection& collection,
    const std::string& code,
    const Dinosaur& updatedDinosaur
);

/*
 * Elimina un dinosaurio y desplaza los registros posteriores.
 * Parámetros: collection, colección que se modifica; code, código buscado.
 * Retorno: true si se eliminó; false si no existe.
 * Complejidad: O(n).
 */
bool deleteDinosaur(
    DinosaurCollection& collection,
    const std::string& code
);

/*
 * Copia un dinosaurio encontrado a la variable result.
 * Parámetros: collection, colección consultada; code, código buscado;
 * result, variable que recibirá el registro.
 * Retorno: true si se encontró; false en caso contrario.
 * Complejidad: O(n).
 */
bool getDinosaurByCode(
    const DinosaurCollection& collection,
    const std::string& code,
    Dinosaur& result
);

#endif