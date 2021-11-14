#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class MouseReleasedEvent : public Event
    {
    public:
        MouseReleasedEvent(int button) : button(button)
        {
        }
        unsigned int GetButton() const { return button; }
        static EventType GetStaticType() { return EventType::MouseReleased; }
        EventType GetType() const override { return EventType::MouseReleased; }
        std::string GetName() const override { return "MouseReleasedEvent"; }
    private:
        int button;
    };
}
