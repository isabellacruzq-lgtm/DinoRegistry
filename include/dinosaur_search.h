#ifndef DINOSAUR_SEARCH_H
#define DINOSAUR_SEARCH_H

#include "dinosaur_collection.h"
#include <cstddef>
#include <string>

// Normaliza un texto para compararlo:
// minúsculas y espacios consecutivos reducidos a uno.
std::string normalizeSearchText(const std::string& text);

// Busca coincidencias parciales en los nombres.
// Guarda índices en results hasta maxResults.
// Devuelve el total de coincidencias encontradas,
// incluso si algunas no caben en results.
std::size_t findDinosaursByName(
    const DinosaurCollection& collection,
    const std::string& query,
    int* results,
    std::size_t maxResults
);

// Comprueba el formato PREFIX-001:
// prefijo de 2 a 10 letras, guion y tres dígitos.
bool isValidDinosaurCode(const std::string& code);

// Genera un código a partir del nombre y busca
// un número secuencial que no esté ocupado.
// Devuelve una cadena vacía si el nombre no aporta letras.
std::string generateDinosaurCode(
    const DinosaurCollection& collection,
    const std::string& name
);

// Cuenta las apariciones de una letra o fragmento
// en todos los nombres. No distingue mayúsculas y
// minúsculas ni espacios adicionales.
std::size_t countOccurrencesInNames(
    const DinosaurCollection& collection,
    const std::string& text
);

// Cuenta grupos de vocales como una aproximación de
// las sílabas de un nombre. No es un análisis lingüístico exacto.
std::size_t countSyllableGroups(const std::string& name);

#endif
