#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class MousePressedEvent : public Event
    {
    public:
        MousePressedEvent(int button) : button(button)
        {
        }
        unsigned int GetButton() const { return button; }
        static EventType GetStaticType() { return EventType::MousePressed; }
        EventType GetType() const override { return EventType::MousePressed; }
        std::string GetName() const override { return "MousePressedEvent"; }
    private:
        int button;
    };
}
