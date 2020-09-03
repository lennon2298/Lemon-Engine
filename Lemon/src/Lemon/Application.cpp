#include "lmpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Lemon
{
    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::CreateWindow());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    Application::~Application() {
        
    }
    
    void Application::PushLayer(Layer* layer) 
    {
        m_LayerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer* overlay) 
    {
        m_LayerStack.PushOverlay(overlay);
    }
    
    void Application::Run() {
        while(m_Running) {
            glClearColor(0.2f, 0.4f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack ) {
                layer->OnUpdate();
            }
            m_Window->OnUpdate();
        }
    }
    
    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

        for ( auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(e);
            if (e.IsHandled()) {
                break;
            }
        }

        LM_CORE_INFO("{0}", e);
    }
    
    bool Application::OnWindowClose(WindowCloseEvent& e) {
        m_Running = false;
        return true;
    }
}
