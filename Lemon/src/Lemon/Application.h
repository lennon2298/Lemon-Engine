#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Lemon/Events/ApplicationEvent.h"
#include "Lemon/Events/MouseEvent.h"
#include "Lemon/Window.h"
#include "Lemon/LayerStack.h"

namespace Lemon {

    class LEMON_API Application {
    public:

        Application();
        virtual ~Application();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void Run();
    private:
        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
    
}
