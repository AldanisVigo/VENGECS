#include "Entity.h"

// Define the global variable once
Entity nextEntity = 0;

// Define the function once
Entity createEntity() {
    return nextEntity++;
}
