#pragma once

#include <string>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Kreckanism/Event/Event.h>

namespace Ksm
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();
        void SetEventCallback(const std::function<void(Event&)>& callback);
        GLFWwindow* GetWindow() const;
        void SetTitle(std::string title) const;
        bool ShouldClose() const;
        void Update() const;
        int GetWidth() const;
        int GetHeight() const;
        void SetWidth(int width) { this->width = width; };
        void SetHeight(int height) { this->height = height; };
    private:
        int width;
        int height;
        std::string title;
        std::function<void(Event&)> eventCallback;
        GLFWwindow* window;
    };
}
