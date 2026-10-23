#ifndef FILE_PERSISTENCE_H
#define FILE_PERSISTENCE_H

#include "dinosaur_collection.h"
#include <string>

// Carga dinosaurios desde un archivo de texto.
// Si no existe, informa y conserva la colección vacía.
bool loadDinosaursFromFile(
    DinosaurCollection& collection,
    const std::string& filename
);

// Guarda la colección completa en un archivo de texto.
bool saveDinosaursToFile(
    const DinosaurCollection& collection,
    const std::string& filename
);

// Lee e imprime el mapa de excavación.
bool readExcavationMap(const std::string& filename);

// Genera un informe legible de la colección.
bool generateReport(
    const DinosaurCollection& collection,
    const std::string& filename
);

#endif
