/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <iostream>

enum class AudioType {
    Music,
    SFX
};

struct AudioClip {
    AudioType type;
    Mix_Music* music = nullptr;
    Mix_Chunk* chunk = nullptr;
};

class AudioManager {
public:
    static bool init(int frequency = 44100, Uint16 format = MIX_DEFAULT_FORMAT, int channels = 2, int chunksize = 2048);
    static void shutdown();

    static bool loadMusic(const std::string& id, const std::string& path);
    static bool loadSFX(const std::string& id, const std::string& path);

    static void playMusic(const std::string& id, int loops = -1);
    static void playSFX(const std::string& id, int loops = 0);

    static void stopMusic();

private:
    static std::unordered_map<std::string, AudioClip> audioClips;
};
