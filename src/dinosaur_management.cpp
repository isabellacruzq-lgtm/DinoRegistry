#include "dinosaur_management.h"
#include <cctype>
#include <cmath>
#include <new>
#include <string>

/*
 * Convierte un texto a minúsculas para comparar códigos.
 * Parámetros: text, texto que se convertirá.
 * Retorno: copia del texto en minúsculas.
 * Complejidad: O(n), donde n es la longitud del texto.
 */
static std::string toLowerCase(const std::string& text) {
    std::string result = text;

    for (std::size_t i = 0; i < result.length(); i++) {
        result[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(result[i]))
        );
    }

    return result;
}

/*
 * Comprueba que un texto no esté vacío ni contenga solo espacios.
 * Parámetros: text, texto que se comprobará.
 * Retorno: true si contiene algún carácter distinto de un espacio.
 * Complejidad: O(n), donde n es la longitud del texto.
 */
static bool hasContent(const std::string& text) {
    return text.find_first_not_of(" \t\r\n") != std::string::npos;
}

/*
 * Comprueba el formato de un código: letras mayúsculas, guion y tres dígitos.
 * Parámetros: code, código que se comprobará.
 * Retorno: true si cumple el formato esperado.
 * Complejidad: O(n), donde n es la longitud del código.
 */
static bool hasValidCodeFormat(const std::string& code) {
    if (code.length() < 5 || code.length() > 7) {
        return false;
    }

    const std::size_t hyphenPosition = code.length() - 4;

    for (std::size_t i = 0; i < hyphenPosition; i++) {
        if (code[i] < 'A' || code[i] > 'Z') {
            return false;
        }
    }

    if (code[hyphenPosition] != '-') {
        return false;
    }

    for (std::size_t i = hyphenPosition + 1; i < code.length(); i++) {
        if (code[i] < '0' || code[i] > '9') {
            return false;
        }
    }

    return true;
}

/*
 * Comprueba que un dinosaurio tenga todos sus datos válidos.
 * Parámetros: dinosaur, dinosaurio que se comprobará.
 * Retorno: true si todos los campos son válidos.
 * Complejidad: O(n), por las comprobaciones de texto.
 */
static bool isValidDinosaur(const Dinosaur& dinosaur) {
    if (!hasContent(dinosaur.code) ||
        !hasValidCodeFormat(dinosaur.code) ||
        !hasContent(dinosaur.name) ||
        !hasContent(dinosaur.period) ||
        !hasContent(dinosaur.diet) ||
        !hasContent(dinosaur.discoverySite)) {
        return false;
    }

    if (!std::isfinite(dinosaur.lengthMeters) ||
        !std::isfinite(dinosaur.weightTons) ||
        !std::isfinite(dinosaur.ageMillionsYears) ||
        dinosaur.lengthMeters < 0.0 ||
        dinosaur.weightTons < 0.0 ||
        dinosaur.ageMillionsYears < 0.0) {
        return false;
    }

    const std::string period = toLowerCase(dinosaur.period);
    const std::string diet = toLowerCase(dinosaur.diet);

    if (period != "triassic" &&
        period != "jurassic" &&
        period != "cretaceous") {
        return false;
    }

    if (diet != "carnivore" &&
        diet != "herbivore" &&
        diet != "omnivore") {
        return false;
    }

    return true;
}

/*
 * Busca un dinosaurio por su código sin distinguir mayúsculas.
 * Parámetros: collection, colección donde se buscará;
 * code, código que se desea encontrar.
 * Retorno: posición del dinosaurio o -1 si no existe.
 * Complejidad: O(n), donde n es la cantidad de dinosaurios.
 */
int findDinosaurByCode(
    const DinosaurCollection& collection,
    const std::string& code
) {
    const std::string searchedCode = toLowerCase(code);

    for (int i = 0; i < collection.count; i++) {
        if (toLowerCase(collection.items[i].code) == searchedCode) {
            return i;
        }
    }

    return -1;
}

/*
 * Aumenta la capacidad de la colección cuando está llena.
 * Parámetros: collection, colección que necesita más espacio.
 * Retorno: true si pudo aumentar la capacidad.
 * Complejidad: O(n), donde n es la cantidad de elementos.
 */
static bool growCollection(DinosaurCollection& collection) {
    int newCapacity = (collection.capacity == 0)
        ? 2
        : collection.capacity * 2;

    Dinosaur* newItems = new (std::nothrow) Dinosaur[newCapacity];

    if (newItems == NULL) {
        return false;
    }

    for (int i = 0; i < collection.count; i++) {
        newItems[i] = collection.items[i];
    }

    delete[] collection.items;

    collection.items = newItems;
    collection.capacity = newCapacity;

    return true;
}

/*
 * Agrega un dinosaurio si sus datos son válidos y su código no existe.
 * Parámetros: collection, colección donde se agregará;
 * dinosaur, datos del nuevo dinosaurio.
 * Retorno: true si se agregó correctamente.
 * Complejidad: O(n), por la búsqueda del código y posible copia.
 */
bool addDinosaur(
    DinosaurCollection& collection,
    const Dinosaur& dinosaur
) {
    if (!isValidDinosaur(dinosaur)) {
        return false;
    }

    if (findDinosaurByCode(collection, dinosaur.code) != -1) {
        return false;
    }

    if (collection.count >= collection.capacity) {
        if (!growCollection(collection)) {
            return false;
        }
    }

    collection.items[collection.count] = dinosaur;
    collection.count++;

    return true;
}

/*
 * Edita los datos de un dinosaurio existente y conserva su código.
 * Parámetros: collection, colección donde está el dinosaurio;
 * code, código del dinosaurio que se editará;
 * replacement, nuevos datos.
 * Retorno: true si se editó correctamente.
 * Complejidad: O(n), por la búsqueda del dinosaurio.
 */
bool editDinosaur(
    DinosaurCollection& collection,
    const std::string& code,
    const Dinosaur& replacement
) {
    int position = findDinosaurByCode(collection, code);

    if (position == -1) {
        return false;
    }

    Dinosaur updatedDinosaur = replacement;
    updatedDinosaur.code = collection.items[position].code;

    if (!isValidDinosaur(updatedDinosaur)) {
        return false;
    }

    collection.items[position] = updatedDinosaur;

    return true;
}

/*
 * Elimina un dinosaurio y desplaza los elementos posteriores.
 * Parámetros: collection, colección donde se encuentra;
 * code, código del dinosaurio que se eliminará.
 * Retorno: true si se eliminó correctamente.
 * Complejidad: O(n), por la búsqueda y el desplazamiento.
 */
bool deleteDinosaur(
    DinosaurCollection& collection,
    const std::string& code
) {
    int position = findDinosaurByCode(collection, code);

    if (position == -1) {
        return false;
    }

    for (int i = position; i < collection.count - 1; i++) {
        collection.items[i] = collection.items[i + 1];
    }

    collection.count--;

    return true;
}

/*
 * Obtiene una copia de un dinosaurio mediante su código.
 * Parámetros: collection, colección donde se buscará;
 * code, código que se desea consultar;
 * result, variable donde se guardará el dinosaurio encontrado.
 * Retorno: true si se encontró el dinosaurio.
 * Complejidad: O(n), por la búsqueda.
 */
bool getDinosaurByCode(
    const DinosaurCollection& collection,
    const std::string& code,
    Dinosaur& result
) {
    int position = findDinosaurByCode(collection, code);

    if (position == -1) {
        return false;
    }

    result = collection.items[position];

    return true;
}
