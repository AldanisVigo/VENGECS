/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include "../../core/scenemanager/Scene.h"
#include "../../core/util/TextureLoader.h"
#include "../../core/entity/Entity.h"

class SceneOne : public Scene {
public:
    void onLoad() override;
    void onUpdate(float dt) override;
    void onUnload() override {}
};
