#pragma once

class Scene {
public:
    virtual ~Scene() = default;

    virtual void onLoad() {}
    virtual void onUpdate(float dt) {}
    virtual void onUnload() {}
};
