# VENGECS

**VENGECS** is a lightweight **C++ ECS (Entity-Component-System) framework** powered by **SDL2**, designed for 2D game development. It provides a modular, fast, and flexible architecture for creating games while keeping systems decoupled and efficient.

---

## Features

- **Entity-Component-System architecture**  
  Organize your game logic cleanly with entities, components, and systems.
- **Animation system**  
  Supports multi-frame sprite animations and horizontal flipping.
- **Physics & Gravity**  
  Rigidbody, collision detection, and gravity for realistic movement.
- **Input handling**  
  Configurable keyboard input system for player controls.
- **Scene management**  
  Switch between scenes while keeping persistent entities alive.
- **SDL2 integration**  
  Easy-to-use wrapper for window and renderer management.
- **SDL2 integration**  
  Particle engine for explosions and other cool effects.


## Future Features
- **Audio**
  Both sound effects and background music.


## Getting Started

### Prerequisites

- C++17 or higher
- SDL2 and SDL2_image installed

**macOS (Homebrew)**

```bash
brew install sdl2 sdl2_image
```

**Linux (APT)**

```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```

**Build**

```bash
mkdir build
cd build
cmake ..
make
```

**Run The Game**

```bash
make run
```
