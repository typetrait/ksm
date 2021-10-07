#pragma once

#include "Kreckanism/Event/Event.h"

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
        virtual std::string GetName() const { return "Window Resize Event!"; }
    private:
        unsigned int width, height;
    };
}