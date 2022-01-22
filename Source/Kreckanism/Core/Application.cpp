#include <Kreckanism/Core/Application.h>

#include <fmt/format.h>

#include <Kreckanism/Core/Logger.h>
#include <Kreckanism/Event/Event.h>
#include <Kreckanism/Event/EventDispatcher.h>
#include <Kreckanism/Event/KeyPressEvent.h>
#include <Kreckanism/Event/MouseMoveEvent.h>
#include <Kreckanism/Event/MousePressEvent.h>
#include <Kreckanism/Event/MouseReleaseEvent.h>
#include <Kreckanism/Event/WindowResizeEvent.h>
#include <Kreckanism/Input/Input.h>

namespace Ksm
{
    void Application::OnUpdate(const double deltaTime)
    {

    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowResizeEvent>([this](const WindowResizeEvent& ev)
        {
            this->OnWindowResize(ev);
        });

        dispatcher.Dispatch<KeyPressEvent>([this](const KeyPressEvent& ev)
        {
            this->OnKeyPress(ev);
        });

        dispatcher.Dispatch<MouseMoveEvent>([this](const MouseMoveEvent& ev)
        {
            this->OnMouseMove(ev);
        });

        dispatcher.Dispatch<MousePressEvent>([this](const MousePressEvent& ev)
        {
            this->OnMousePress(ev);
        });

        dispatcher.Dispatch<MouseReleaseEvent>([this](const MouseReleaseEvent& ev)
        {
            this->OnMouseRelease(ev);
        });
    }

    void Application::OnWindowResize(const WindowResizeEvent& ev)
    {
        //KLOG_INFO(fmt::format("Window resized: Width={}, Height={}.", ev.GetWidth(), ev.GetHeight()));
    }

    void Application::OnKeyPress(const KeyPressEvent& ev)
    {
        //KLOG_INFO(fmt::format("Key pressed: KeyCode={}.", ev.GetKeyCode()));
    }

    void Application::OnMouseMove(const MouseMoveEvent& ev)
    {
        //KLOG_INFO(fmt::format("Mouse moved: X={}, Y={}.", ev.GetX(), ev.GetY()));
    }

    void Application::OnMousePress(const MousePressEvent& ev)
    {
        ///KLOG_INFO(fmt::format("Mouse pressed: Button={}.", ev.GetButton()));
    }

    void Application::OnMouseRelease(const MouseReleaseEvent& ev)
    {
        ///KLOG_INFO(fmt::format("Mouse released: Button={}.", ev.GetButton()));
    }
}
