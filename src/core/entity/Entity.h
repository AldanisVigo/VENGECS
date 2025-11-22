#pragma once
#include <cstddef> // for std::size_t

using Entity = std::size_t;

// Declare, don't define
extern Entity nextEntity;
Entity createEntity();
