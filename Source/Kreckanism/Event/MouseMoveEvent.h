#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class MouseMoveEvent : public Event
    {
    public:
        MouseMoveEvent(double x, double y) : x(x), y(y)
        {
        }
        double GetX() const { return x; }
        double GetY() const { return y; }
        static EventType GetStaticType() { return EventType::MouseMove; }
        EventType GetType() const override { return EventType::MouseMove; }
        std::string GetName() const override { return "MouseMoveEvent"; }
    private:
        double x, y;
    };
}
