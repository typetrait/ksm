#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(unsigned int keyCode) : keyCode(keyCode)
        {
        }
        unsigned int GetKeyCode() const { return keyCode; }
        static EventType GetStaticType() { return EventType::KeyPress; }
        EventType GetType() const override { return EventType::KeyPress; }
        std::string GetName() const override { return "KeyPressEvent"; }

    private:
        unsigned int keyCode;
    };
}
