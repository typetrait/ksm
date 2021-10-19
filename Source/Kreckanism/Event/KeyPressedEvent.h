#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class KeyPressedEvent : public Event
    {
    public:
        KeyPressedEvent(unsigned int keyCode) : keyCode(keyCode)
        {
        }
        unsigned int GetKeyCode() const { return keyCode; }
        static EventType GetStaticType() { return EventType::KeyPressed; }
        EventType GetType() const override { return EventType::KeyPressed; }
        std::string GetName() const override { return "Key Pressed Event!"; }
    private:
        unsigned int keyCode;
    };
}
