#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Core.h"
#include "Log.h"
#include "Events/Event.h"
#include "Lemon/Events/ApplicationEvent.h"
#include "Lemon/Events/MouseEvent.h"
#include "Window.h"
namespace Lemon {

    class LEMON_API Application {
    public:

        Application();
        virtual ~Application();

        void Run();
    private:
        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application* CreateApplication();
    
}
