/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "Game/Game.h"
#include <iostream>

int main() {
    Game game;
    if (!game.init("VENGecs", 1024, 1080, false)) {
        std::cout << "Failed to initialize SDL / game\n"; 
        return 1; // Failed to initialize SDL / game
    }

    game.run();      // This contains the main loop with window focus handling
    game.shutdown(); // Clean up SDL, scenes, etc.

    return 0;
}

