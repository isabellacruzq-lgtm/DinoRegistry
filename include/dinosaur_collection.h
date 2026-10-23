#ifndef DINOSAUR_COLLECTION_H
#define DINOSAUR_COLLECTION_H

#include "dinosaur.h"
#include <cstddef>

struct DinosaurCollection {
    Dinosaur* items;
    std::size_t count;
    std::size_t capacity;
};

void initializeCollection(DinosaurCollection& collection);
void freeCollection(DinosaurCollection& collection);

#endif
