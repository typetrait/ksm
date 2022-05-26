#pragma once

#include <glm/glm.hpp>

#include <fmod_studio.hpp>
#include <fmod.hpp>

#include <string>
#include <map>

namespace Ksm
{
    class AudioEngine
    {
    public:
        static void Initialize();
        static void Update();
        static void Shutdown();
        static bool IsError(FMOD_RESULT result);

        static void LoadBank(const std::string& name, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
        static void LoadEvent(const std::string& name);
        static void LoadSound(const std::string& name, bool is3D = true, bool isLooping = false, bool shouldStream = false);
        static void UnloadSound(const std::string& name);

        static int PlaySound(const std::string& name, const glm::vec3& position, float volumedB);
        static void PlayEvent(const std::string& name);
        static void StopEvent(const std::string& name, bool shouldFadeout);
        static bool IsEventPlaying(const std::string& name);
        static float GetEventParameter(const std::string& eventName, const std::string& parameterName);
        static void SetEventParameter(const std::string& eventName, const std::string& parameterName, float value);

    private:
        inline static FMOD::Studio::System* system;

        inline static int nextChannelId;

        inline static std::map<std::string, FMOD::Studio::Bank*> banks;
        inline static std::map<std::string, FMOD::Studio::EventInstance*> events;
        inline static std::map<std::string, FMOD::Sound*> sounds;
        inline static std::map<int, FMOD::Channel*> channels;
    };
}
