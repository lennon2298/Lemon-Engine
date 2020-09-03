#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Lemon/Window.h"
#include "Lemon/Log.h"
#include "Lemon/Events/ApplicationEvent.h"
#include "Lemon/Events/KeyEvent.h"
#include "Lemon/Events/MouseEvent.h"

namespace Lemon {
    class WindowsWindow : public Window {
    private:
        GLFWwindow* m_Window;

        struct WindowsData {
            std::string m_Title;
            unsigned int m_Width;
            unsigned int m_Height;
            bool m_VSync;

            EventCallbackFn EventCallback;
        };

        WindowsData m_Data;

    public:
        WindowsWindow(const WindowsProp& prop);
        virtual ~WindowsWindow();

        void OnUpdate() override;
        inline unsigned int GetWidth() const override { return m_Data.m_Width; }
        inline unsigned int GetHeight() const override { return m_Data.m_Height; }

        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() override;

    private:
        virtual void Init(const WindowsProp& prop);
        virtual void Shutdown();
    };
}
