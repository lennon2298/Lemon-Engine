#pragma once
#include "lmpch.h"
#include "Lemon/Core.h"
#include "Lemon/Events/Event.h"

namespace Lemon {
    struct WindowsProp {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowsProp(const std::string& title = "Lemon Engine", unsigned int width = 1280, unsigned int height = 720)
        :Title(title), Width(width), Height(height) {}
    };

    class LEMON_API Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~Window() {};

        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() = 0;

        static Window* CreateWindow(const WindowsProp& prop = WindowsProp());
    };
}
