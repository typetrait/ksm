#pragma once

#include <Kreckanism/Event/Event.h>
#include <Kreckanism/Event/KeyPressEvent.h>
#include <Kreckanism/Event/MouseMoveEvent.h>
#include <Kreckanism/Event/MousePressEvent.h>
#include <Kreckanism/Event/MouseReleaseEvent.h>
#include <Kreckanism/Event/WindowResizeEvent.h>

namespace Ksm
{
    class Application
    {
    public:
        virtual void Startup() = 0;
        virtual void Run() = 0;
        virtual void Exit() = 0;
        virtual void OnUpdate(const double deltaTime);
        virtual void OnEvent(Event& ev);

    protected:
        virtual void OnWindowResize(const WindowResizeEvent& ev);
        virtual void OnKeyPress(const KeyPressEvent& ev);
        virtual void OnMouseMove(const MouseMoveEvent& ev);
        virtual void OnMousePress(const MousePressEvent& ev);
        virtual void OnMouseRelease(const MouseReleaseEvent& ev);
    };
}
