/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "SceneManager.h"
#include <iostream>

std::unordered_map<std::string, Scene*> SceneManager::scenes;
Scene* SceneManager::current = nullptr;
bool SceneManager::windowFocused = true;

void SceneManager::addScene(const std::string& name, Scene* scene) {
    scenes[name] = scene;
}

void SceneManager::switchTo(const std::string& name) {
    if (!scenes.count(name)) {
        std::cerr << "Scene not found: " << name << std::endl;
        return;
    }

    // Unload old scene
    if (current) {
        current->onUnload();
    }

    // Switch
    current = scenes[name];

    // Load new
    if (current) {
        current->onLoad();
    }
}

void SceneManager::update(float dt) {
    if (current) {
        current->onUpdate(dt);
    }
}

void SceneManager::unloadCurrent() {
    if (current) {
        current->onUnload();
        current = nullptr;
    }
}
