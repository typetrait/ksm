#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class MouseReleaseEvent : public Event
    {
    public:
        MouseReleaseEvent(int button) : button(button)
        {
        }
        unsigned int GetButton() const { return button; }
        static EventType GetStaticType() { return EventType::MouseRelease; }
        EventType GetType() const override { return EventType::MouseRelease; }
        std::string GetName() const override { return "MouseReleaseEvent"; }
    private:
        int button;
    };
}
