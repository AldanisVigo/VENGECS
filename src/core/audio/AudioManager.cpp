/*
    Author: Aldanis Vigo <aldanisvigo@gmail.com>
    Date: Sat Nov 22 2025
*/

#include "AudioManager.h"

std::unordered_map<std::string, AudioClip> AudioManager::audioClips;

bool AudioManager::init(int frequency, Uint16 format, int channels, int chunksize) {
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
        return false;
    }
    return true;
}

void AudioManager::shutdown() {
    for (auto& [id, clip] : audioClips) {
        if (clip.type == AudioType::Music && clip.music) Mix_FreeMusic(clip.music);
        if (clip.type == AudioType::SFX && clip.chunk) Mix_FreeChunk(clip.chunk);
    }
    audioClips.clear();
    Mix_CloseAudio();
}

bool AudioManager::loadMusic(const std::string& id, const std::string& path) {
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music) {
        std::cerr << "Failed to load music: " << Mix_GetError() << "\n";
        return false;
    }
    audioClips[id] = { AudioType::Music, music, nullptr };
    return true;
}

bool AudioManager::loadSFX(const std::string& id, const std::string& path) {
    Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
    if (!chunk) {
        std::cerr << "Failed to load SFX: " << Mix_GetError() << "\n";
        return false;
    }
    audioClips[id] = { AudioType::SFX, nullptr, chunk };
    return true;
}

void AudioManager::playMusic(const std::string& id, int loops) {
    auto it = audioClips.find(id);
    if (it != audioClips.end() && it->second.type == AudioType::Music) {
        Mix_PlayMusic(it->second.music, loops);
    }
}

void AudioManager::playSFX(const std::string& id, int loops) {
    auto it = audioClips.find(id);
    if (it != audioClips.end() && it->second.type == AudioType::SFX) {
        Mix_PlayChannel(-1, it->second.chunk, loops);
    }
}

void AudioManager::stopMusic() {
    Mix_HaltMusic();
}
