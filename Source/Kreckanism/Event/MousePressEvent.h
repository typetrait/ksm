#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class MousePressEvent : public Event
    {
    public:
        MousePressEvent(int button) : button(button)
        {
        }
        unsigned int GetButton() const { return button; }
        static EventType GetStaticType() { return EventType::MousePress; }
        EventType GetType() const override { return EventType::MousePress; }
        std::string GetName() const override { return "MousePressEvent"; }
    private:
        int button;
    };
}
