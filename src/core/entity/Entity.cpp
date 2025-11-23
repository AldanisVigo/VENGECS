/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "Entity.h"

// Define the global variable once
Entity nextEntity = 0;

// Define the function once
Entity createEntity() {
    return nextEntity++;
}
