#include "dinosaur_management.h"
#include <cctype>
#include <new>

/*
 * Convierte un texto a minúsculas para comparar códigos sin distinguir
 * entre mayúsculas y minúsculas.
 * Parámetros: text, texto que se convertirá.
 * Retorno: una copia en minúsculas.
 * Complejidad: O(m), donde m es la longitud del texto.
 */
static std::string toLowerCase(const std::string& text) {
    std::string result = text;

    for (std::size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

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
) {
    const std::string target = toLowerCase(code);

    for (std::size_t i = 0; i < collection.count; ++i) {
        if (toLowerCase(collection.items[i].code) == target) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

/*
 * Amplía la capacidad de la colección, copia los registros y libera
 * el arreglo anterior.
 * Parámetros: collection, colección que necesita más espacio.
 * Retorno: true si la ampliación tuvo éxito; false si falló la reserva.
 * Complejidad: O(n), por la copia de los registros existentes.
 */
static bool growCollection(DinosaurCollection& collection) {
    const std::size_t newCapacity =
        (collection.capacity == 0)
            ? 2
            : collection.capacity * 2;

    // nothrow permite comprobar el fallo de reserva sin lanzar una excepción.
    Dinosaur* newItems = new (std::nothrow) Dinosaur[newCapacity];

    if (newItems == nullptr) {
        return false;
    }

    // Copiar antes de liberar garantiza que los datos no se pierdan.
    for (std::size_t i = 0; i < collection.count; ++i) {
        newItems[i] = collection.items[i];
    }

    delete[] collection.items;

    collection.items = newItems;
    collection.capacity = newCapacity;

    return true;
}

/*
 * Agrega un dinosaurio si su código no está repetido.
 * Parámetros: collection, colección que se modifica; dinosaur, registro nuevo.
 * Retorno: true si se agregó; false si el código está vacío, repetido
 * o no se pudo reservar memoria.
 * Complejidad: O(n) por la búsqueda y la posible ampliación.
 */
bool addDinosaur(
    DinosaurCollection& collection,
    const Dinosaur& dinosaur
) {
    if (dinosaur.code.empty()) {
        return false;
    }

    if (findDinosaurByCode(collection, dinosaur.code) != -1) {
        return false;
    }

    if (collection.count == collection.capacity) {
        if (!growCollection(collection)) {
            return false;
        }
    }

    collection.items[collection.count] = dinosaur;
    ++collection.count;

    return true;
}

/*
 * Edita los datos de un dinosaurio existente y conserva su código original.
 * Parámetros: collection, colección que se modifica; code, código original;
 * updatedDinosaur, datos nuevos.
 * Retorno: true si se editó; false si no existe el código.
 * Complejidad: O(n).
 */
bool editDinosaur(
    DinosaurCollection& collection,
    const std::string& code,
    const Dinosaur& updatedDinosaur
) {
    const int index = findDinosaurByCode(collection, code);

    if (index == -1) {
        return false;
    }

    Dinosaur replacement = updatedDinosaur;
    replacement.code = collection.items[index].code;

    collection.items[index] = replacement;

    return true;
}

/*
 * Elimina un dinosaurio y desplaza los registros posteriores.
 * Parámetros: collection, colección que se modifica; code, código buscado.
 * Retorno: true si se eliminó; false si no existe.
 * Complejidad: O(n).
 */
bool deleteDinosaur(
    DinosaurCollection& collection,
    const std::string& code
) {
    const int foundIndex = findDinosaurByCode(collection, code);

    if (foundIndex == -1) {
        return false;
    }

    const std::size_t index =
        static_cast<std::size_t>(foundIndex);

    for (std::size_t i = index; i + 1 < collection.count; ++i) {
        collection.items[i] = collection.items[i + 1];
    }

    --collection.count;

    return true;
}

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
) {
    const int index = findDinosaurByCode(collection, code);

    if (index == -1) {
        return false;
    }

    result = collection.items[index];

    return true;
}
