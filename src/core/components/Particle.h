#pragma once

struct Particle {
    float x;
    float y;
    float vx;        // velocity X
    float vy;        // velocity Y
    float scale;
    float opacity;
    float lifetime;  // remaining life in seconds
};
