#include "dinosaur_search.h"
#include "dinosaur_management.h"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>

// Convierte texto a minúsculas y convierte varios espacios
// consecutivos en un único espacio, sin alterar el texto original.
std::string normalizeSearchText(const std::string& text) {
    std::string result;
    bool pendingSpace = false;

    for (std::size_t i = 0; i < text.size(); ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(text[i]);

        if (std::isspace(ch)) {
            if (!result.empty()) {
                pendingSpace = true;
            }
        } else {
            if (pendingSpace) {
                result += ' ';
                pendingSpace = false;
            }

            result += static_cast<char>(std::tolower(ch));
        }
    }

    return result;
}

std::size_t findDinosaursByName(
    const DinosaurCollection& collection,
    const std::string& query,
    int* results,
    std::size_t maxResults
) {
    const std::string target = normalizeSearchText(query);

    if (target.empty()) {
        return 0;
    }

    std::size_t matches = 0;

    for (std::size_t i = 0; i < collection.count; ++i) {
        const std::string name =
            normalizeSearchText(collection.items[i].name);

        if (name.find(target) != std::string::npos) {
            if (results != nullptr && matches < maxResults) {
                results[matches] = static_cast<int>(i);
            }

            ++matches;
        }
    }

    return matches;
}

bool isValidDinosaurCode(const std::string& code) {
    const std::size_t separator = code.find('-');

    if (separator < 2 || separator > 10 ||
        separator == std::string::npos ||
        code.size() != separator + 4) {
        return false;
    }

    for (std::size_t i = 0; i < separator; ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(code[i]);

        if (!std::isalpha(ch) || !std::isupper(ch)) {
            return false;
        }
    }

    if (code[separator] != '-') {
        return false;
    }

    for (std::size_t i = separator + 1; i < code.size(); ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(code[i]);

        if (!std::isdigit(ch)) {
            return false;
        }
    }

    return true;
}

std::string generateDinosaurCode(
    const DinosaurCollection& collection,
    const std::string& name
) {
    std::string prefix;

    for (std::size_t i = 0; i < name.size() && prefix.size() < 3; ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(name[i]);

        if (std::isalpha(ch)) {
            prefix += static_cast<char>(std::toupper(ch));
        }
    }

    if (prefix.size() < 2) {
        return "";
    }

    for (unsigned int number = 1; number <= 999; ++number) {
        std::ostringstream stream;
        stream << prefix << '-'
               << std::setfill('0') << std::setw(3) << number;

        const std::string candidate = stream.str();

        if (findDinosaurByCode(collection, candidate) == -1) {
            return candidate;
        }
    }

    return "";
}

std::size_t countOccurrencesInNames(
    const DinosaurCollection& collection,
    const std::string& text
) {
    const std::string target = normalizeSearchText(text);

    if (target.empty()) {
        return 0;
    }

    std::size_t total = 0;

    for (std::size_t i = 0; i < collection.count; ++i) {
        const std::string name =
            normalizeSearchText(collection.items[i].name);

        std::size_t position = 0;

        while ((position = name.find(target, position))
               != std::string::npos) {
            ++total;
            position += target.size();
        }
    }

    return total;
}

std::size_t countSyllableGroups(const std::string& name) {
    std::size_t groups = 0;
    bool previousWasVowel = false;

    for (std::size_t i = 0; i < name.size(); ++i) {
        const unsigned char ch =
            static_cast<unsigned char>(
                std::tolower(static_cast<unsigned char>(name[i]))
            );

        const bool isVowel =
            ch == 'a' || ch == 'e' || ch == 'i' ||
            ch == 'o' || ch == 'u';

        if (isVowel && !previousWasVowel) {
            ++groups;
        }

        previousWasVowel = isVowel;
    }

    return groups;
}
