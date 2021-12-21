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

    private:
        void OnWindowResize(const WindowResizeEvent& ev);
        void OnKeyPress(const KeyPressEvent& ev);
        void OnMouseMove(const MouseMoveEvent& ev);
        void OnMousePress(const MousePressEvent& ev);
        void OnMouseRelease(const MouseReleaseEvent& ev);
    };
}
