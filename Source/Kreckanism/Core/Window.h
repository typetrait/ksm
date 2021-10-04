#pragma once

#include <string>
#include <functional>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Kreckanism/Event/Event.h"

namespace Ksm
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();
        void SetEventCallback(const std::function<void(Event&)>& callback);
        void SetTitle(std::string title) const;
        bool ShouldClose() const;
        void Update() const;
    private:
        int width;
        int height;
        std::string title;
        std::function<void(Event&)> eventCallback;
        GLFWwindow* window;
    };
}
