#include "file_persistence.h"
#include "dinosaur_management.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

namespace {

// Divide una línea por el separador |.
bool splitDinosaurLine(
    const std::string& line,
    Dinosaur& dinosaur
) {
    std::stringstream stream(line);
    std::string fields[8];

    for (int i = 0; i < 8; ++i) {
        if (!std::getline(stream, fields[i], '|')) {
            return false;
        }
    }

    // Rechaza campos adicionales.
    std::string extra;
    if (std::getline(stream, extra, '|')) {
        return false;
    }

    try {
        dinosaur.code = fields[0];
        dinosaur.name = fields[1];
        dinosaur.period = fields[2];
        dinosaur.diet = fields[3];
        dinosaur.lengthMeters = std::stod(fields[4]);
        dinosaur.weightTons = std::stod(fields[5]);
        dinosaur.ageMillionsYears = std::stod(fields[6]);
        dinosaur.discoverySite = fields[7];
    } catch (const std::exception&) {
        return false;
    }

    return !dinosaur.code.empty() && !dinosaur.name.empty();
}

} // namespace

bool loadDinosaursFromFile(
    DinosaurCollection& collection,
    const std::string& filename
) {
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cout << "No se encontro " << filename
                  << ". Se iniciara con una coleccion vacia.\n";
        return false;
    }

    std::string line;
    int lineNumber = 0;
    int loaded = 0;
    int skipped = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        if (line.empty()) {
            continue;
        }

        Dinosaur dinosaur;

        if (!splitDinosaurLine(line, dinosaur)) {
            std::cerr << "Aviso: linea " << lineNumber
                      << " invalida en " << filename
                      << "; se omitira.\n";
            ++skipped;
            continue;
        }

        // Reutiliza la funcion de gestion existente.
        if (!addDinosaur(collection, dinosaur)) {
            std::cerr << "Aviso: no se pudo agregar el codigo "
                      << dinosaur.code << " de la linea "
                      << lineNumber << ".\n";
            ++skipped;
            continue;
        }

        ++loaded;
    }

    if (file.bad()) {
        std::cerr << "Error al leer " << filename << ".\n";
        return false;
    }

    std::cout << "Dinosaurios cargados: " << loaded << ".\n";

    if (skipped > 0) {
        std::cout << "Lineas omitidas: " << skipped << ".\n";
    }

    return true;
}

bool saveDinosaursToFile(
    const DinosaurCollection& collection,
    const std::string& filename
) {
    std::ofstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filename
                  << " para escritura.\n";
        return false;
    }

    file << std::setprecision(15);

    for (std::size_t i = 0; i < collection.count; ++i) {
        const Dinosaur& d = collection.items[i];

        file << d.code << '|'
             << d.name << '|'
             << d.period << '|'
             << d.diet << '|'
             << d.lengthMeters << '|'
             << d.weightTons << '|'
             << d.ageMillionsYears << '|'
             << d.discoverySite << '\n';

        if (!file) {
            std::cerr << "Error al escribir un dinosaurio en "
                      << filename << ".\n";
            return false;
        }
    }

    file.close();

    if (!file) {
        std::cerr << "Error al finalizar la escritura de "
                  << filename << ".\n";
        return false;
    }

    std::cout << "Coleccion guardada en " << filename << ".\n";
    return true;
}

bool readExcavationMap(const std::string& filename) {
    std::ifstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Aviso: no se pudo abrir " << filename
                  << ". El mapa no esta disponible.\n";
        return false;
    }

    std::cout << "\n========== MAPA DE EXCAVACION ==========\n";

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    if (file.bad()) {
        std::cerr << "Error al leer " << filename << ".\n";
        return false;
    }

    std::cout << "========================================\n\n";
    return true;
}

bool generateReport(
    const DinosaurCollection& collection,
    const std::string& filename
) {
    std::ofstream file(filename.c_str());

    if (!file.is_open()) {
        std::cerr << "Error: no se pudo crear " << filename << ".\n";
        return false;
    }

    file << "REPORTE DE DINOSAURIOS\n";
    file << "======================\n\n";
    file << "Total de dinosaurios: " << collection.count << "\n\n";

    if (collection.count == 0) {
        file << "La coleccion esta vacia.\n";
    } else {
        file << std::fixed << std::setprecision(2);

        for (std::size_t i = 0; i < collection.count; ++i) {
            const Dinosaur& d = collection.items[i];

            file << "Codigo: " << d.code << '\n';
            file << "Nombre: " << d.name << '\n';
            file << "Periodo: " << d.period << '\n';
            file << "Dieta: " << d.diet << '\n';
            file << "Longitud: " << d.lengthMeters << " metros\n";
            file << "Peso: " << d.weightTons << " toneladas\n";
            file << "Antiguedad: " << d.ageMillionsYears
                 << " millones de anos\n";
            file << "Lugar de descubrimiento: "
                 << d.discoverySite << "\n\n";
        }
    }

    file.close();

    if (!file) {
        std::cerr << "Error al finalizar la escritura de "
                  << filename << ".\n";
        return false;
    }

    std::cout << "Reporte generado en " << filename << ".\n";
    return true;
}
