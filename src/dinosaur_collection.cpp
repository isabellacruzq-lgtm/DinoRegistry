#include "dinosaur_collection.h"

void initializeCollection(DinosaurCollection& collection) {
    collection.items = nullptr;
    collection.count = 0;
    collection.capacity = 0;
}

void freeCollection(DinosaurCollection& collection) {
    delete[] collection.items;
    collection.items = nullptr;
    collection.count = 0;
    collection.capacity = 0;
}
