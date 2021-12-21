#pragma once

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : width(width), height(height)
        {
        }
        unsigned int GetWidth() const { return width; }
        unsigned int GetHeight() const { return height; }
        static EventType GetStaticType() { return EventType::WindowResize; }
        EventType GetType() const override { return EventType::WindowResize; }
        std::string GetName() const override { return "WindowResizeEvent"; }

    private:
        unsigned int width, height;
    };
}
