#include <Kreckanism/Audio/AudioEngine.h>

#include <Kreckanism/Core/Logger.h>

#include <string>
#include <vector>
#include <map>

#include <fmt/format.h>

#include <fmod_studio.hpp>
#include <fmod_studio_common.h>
#include <fmod_errors.h>
#include <fmod.hpp>

namespace Ksm
{
    void AudioEngine::Initialize()
    {
        FMOD_RESULT result;
        system = nullptr;

        // Create the Studio System object.
        result = FMOD::Studio::System::create(&system);
        if (IsError(result))
        {
            auto reason = FMOD_ErrorString(result);
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to initialize FMOD! {} {}.", result, reason));
        }

        // Initialize FMOD Studio, which will also initialize FMOD Core.
        result = system->initialize(512, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0);
        if (IsError(result))
        {
            auto reason = FMOD_ErrorString(result);
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to initialize FMOD! {} {}.", result, reason));
        }
    }

    void AudioEngine::Update()
    {
        std::vector<std::map<int, FMOD::Channel*>::iterator> stoppedChannels;

        for (auto it = channels.begin(), end = channels.end(); it != end; ++it)
        {
            bool isPlaying = false;
            it->second->isPlaying(&isPlaying);

            if (!isPlaying)
            {
                stoppedChannels.push_back(it);
            }
        }

        for (auto& it : stoppedChannels)
        {
            channels.erase(it);
        }

        if (IsError(system->update()))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed update call"));
        }
    }

    void AudioEngine::Shutdown()
    {
        system->unloadAll();
        system->release();
    }

    bool AudioEngine::IsError(FMOD_RESULT result)
    {
        return result != FMOD_OK;
    }

    void AudioEngine::LoadBank(const std::string& name, FMOD_STUDIO_LOAD_BANK_FLAGS flags)
    {
        auto it = banks.find(name);
        if (it != banks.end())
        {
            return;
        }

        FMOD::Studio::Bank* bank = nullptr;
        if (IsError(system->loadBankFile(name.c_str(), flags, &bank)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to load bank file \"{}\".", name));
        }

        if (bank)
        {
            banks[name] = bank;
        }
    }

    void AudioEngine::LoadEvent(const std::string& name)
    {
        auto it = events.find(name);
        if (it != events.end())
        {
            return;
        }

        FMOD::Studio::EventDescription* eventDescription = nullptr;
        if (IsError(system->getEvent(name.c_str(), &eventDescription)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to load event \"{}\".", name));
            return;
        }

        if (eventDescription)
        {
            FMOD::Studio::EventInstance* eventInstance = nullptr;

            if (IsError(eventDescription->createInstance(&eventInstance)))
            {
                KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to create event instance \"{}\".", name));
            }

            if (eventInstance)
            {
                events[name] = eventInstance;
            }
        }
    }

    void AudioEngine::LoadSound(const std::string& name, bool is3D, bool isLooping, bool shouldStream)
    {
        auto it = sounds.find(name);
        if (it != sounds.end())
        {
            return;
        }

        FMOD_MODE mode = FMOD_DEFAULT;
        mode |= is3D ? FMOD_3D : FMOD_2D;
        mode |= isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
        mode |= shouldStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

        FMOD::System* lowLevelSystem = nullptr;
        if (IsError(system->getCoreSystem(&lowLevelSystem)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to get low level system."));
        }

        FMOD::Sound* sound = nullptr;
        if (IsError(lowLevelSystem->createSound(name.c_str(), mode, nullptr, &sound)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to load sound \"{}\".", name));
        }

        if (sound)
        {
            sounds[name] = sound;
        }
    }

    void AudioEngine::UnloadSound(const std::string& name)
    {
        auto it = sounds.find(name);
        if (it == sounds.end())
        {
            return;
        }

        if (IsError(it->second->release()))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to unload sound \"{}\".", name));
        }

        sounds.erase(name);
    }

    int AudioEngine::PlaySound(const std::string& name, const glm::vec3& position, float volumedB)
    {
        int currentChannelId = nextChannelId++;

        auto it = sounds.find(name);
        if (it == sounds.end())
        {
            LoadSound(name);
            return currentChannelId;
        }

        FMOD::System* lowLevelSystem = nullptr;
        if (IsError(system->getCoreSystem(&lowLevelSystem)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to get low level system."));
        }

        FMOD::Channel* channel = nullptr;
        if (IsError(lowLevelSystem->playSound(it->second, nullptr, true, &channel)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to play sound \"{}\".", name));
        }

        if (channel)
        {
            FMOD_MODE mode;
            it->second->getMode(&mode);

            if (mode & FMOD_3D)
            {
                FMOD_VECTOR fModPosition{};
                fModPosition.x = position.x;
                fModPosition.y = position.y;
                fModPosition.z = position.z;

                if (IsError(channel->set3DAttributes(&fModPosition, nullptr)))
                {
                    KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to set channel 3D attributes \"{}\".", currentChannelId));
                }
            }

            auto failed = IsError(channel->setVolume(volumedB)) || IsError(channel->setPaused(false));

            if (failed)
            {
                KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to set channel properties \"{}\".", currentChannelId));
                channels[currentChannelId] = channel;
            }
        }

        return currentChannelId;
    }

    void AudioEngine::PlayEvent(const std::string& name)
    {
        auto it = events.find(name);
        if (it == events.end())
        {
            LoadEvent(name);

            it = events.find(name);
            if (it == events.end())
            {
                return;
            }
        }

        it->second->start();
    }

    void AudioEngine::StopEvent(const std::string& name, bool shouldFadeout)
    {
        auto it = events.find(name);
        if (it == events.end())
        {
            return;
        }

        FMOD_STUDIO_STOP_MODE mode;
        mode = shouldFadeout ? FMOD_STUDIO_STOP_ALLOWFADEOUT : FMOD_STUDIO_STOP_IMMEDIATE;

        if (IsError(it->second->stop(mode)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to stop event \"{}\".", name));
        }
    }

    bool AudioEngine::IsEventPlaying(const std::string& name)
    {
        auto it = events.find(name);
        if (it == events.end())
        {
            return false;
        }

        FMOD_STUDIO_PLAYBACK_STATE* state = nullptr;
        if (it->second->getPlaybackState(state) == FMOD_STUDIO_PLAYBACK_PLAYING)
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to get event playback state \"{}\".", name));
            return true;
        }

        return false;
    }

    float AudioEngine::GetEventParameter(const std::string& eventName, const std::string& parameterName)
    {
        auto it = events.find(eventName);
        if (it == events.end())
        {
            return 0.0f;
        }

        float value = 0.0f;
        if (IsError(it->second->getParameterByName(parameterName.c_str(), &value)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to get event \"{}\" parameter \"{}\".", eventName, parameterName));
        }

        return value;
    }

    void AudioEngine::SetEventParameter(const std::string& eventName, const std::string& parameterName, float value)
    {
        auto it = events.find(eventName);
        if (it == events.end())
        {
            return;;
        }

        if (IsError(it->second->setParameterByName(parameterName.c_str(), value)))
        {
            KLOG_FAIL(fmt::format("Ksm::AudioEngine failed to set event \"{}\" parameter \"{}\".", eventName, parameterName));
        }
    }
}
