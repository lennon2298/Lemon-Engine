#include "lmpch.h"
#include "GLFWWindow.h"

namespace Lemon
{
    static bool s_GLFWInitialized = false;
    static bool s_GLADInitialized = false;

    static void GLFWErrorCallback(int error, const char* description) {
        LM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    WindowsWindow::WindowsWindow(const WindowsProp& prop) {
        Init(prop);
    }
    
    WindowsWindow::~WindowsWindow() {
        Shutdown();
    }
    
    Window* Window::CreateWindow(const WindowsProp& prop) {
        return new WindowsWindow(prop);
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }
    
    void WindowsWindow::SetVSync(bool enabled) {
        m_Data.m_VSync = enabled;
        if(enabled)
            glfwSwapInterval(1);
        else   
            glfwSwapInterval(0);
    }
    
    bool WindowsWindow::IsVSync() {
        return m_Data.m_VSync;
    }
    
    void WindowsWindow::Init(const WindowsProp& prop) {
        m_Data.m_Title = prop.Title;
        m_Data.m_Width = prop.Width;
        m_Data.m_Height = prop.Height;

        LM_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.m_Title, m_Data.m_Width, m_Data.m_Height);

        if(!s_GLFWInitialized) {
            int success = glfwInit();
            LM_CORE_ASSERT(success, "Failed to Initialize GLFW")
            LM_CORE_INFO("Initialized GLFW");
            s_GLFWInitialized = true;
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif

        m_Window = glfwCreateWindow(m_Data.m_Width, m_Data.m_Height, m_Data.m_Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(false);

        if(!s_GLADInitialized) {
            int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            LM_CORE_ASSERT(success, "Failed to Initialize Glad");
            LM_CORE_INFO("Initialized Glad");
            s_GLADInitialized = true;
        }

        //GLFW Callbacks

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            Data.m_Width = width;
            Data.m_Height = height;
            WindowResizeEvent event(width, height);
            Data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window){
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent event;
            Data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:{
                    KeyPressedEvent event(key, 0);
                    Data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:{
                    KeyReleasedEvent event(key);
                    Data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:{
                    KeyPressedEvent event(key, 1);
                    Data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow * window, int button, int action, int mods){
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            switch (action)
            {
                case GLFW_PRESS:{
                    MouseButtonPressedEvent event(button);
                    Data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:{
                    MouseButtonReleasedEvent event(button);
                    Data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos){
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)xPos, (float)yPos);
            Data.EventCallback(event);
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset){
            WindowsData& Data = *(WindowsData*)glfwGetWindowUserPointer(window);
            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            Data.EventCallback(event);
        });
    }
    
    void WindowsWindow::Shutdown() {
        glfwDestroyWindow(m_Window);
    }
}
