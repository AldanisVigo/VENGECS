/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once

class Scene {
public:
    virtual ~Scene() = default;
    virtual void onLoad() {}
    virtual void onUpdate(float dt) {}
    virtual void onUnload() {}
};
