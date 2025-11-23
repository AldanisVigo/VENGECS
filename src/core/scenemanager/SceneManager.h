#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>

class SceneManager {
public:
    static bool windowFocused;
    static void addScene(const std::string& name, Scene* scene);
    static void switchTo(const std::string& name);
    static void update(float dt);
    static void unloadCurrent();

private:
    static std::unordered_map<std::string, Scene*> scenes;
    static Scene* current;
};
