#pragma once

#include "Event.h"

namespace Lemon {
    class WindowResizeEvent : public Event {
    private:
        unsigned int m_Width, m_Height;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
        : m_Width(width), m_Height(height) {}

        inline unsigned int GetWindowWidth() const { return m_Width; }
        inline unsigned int GetWindowHeight() const { return m_Height; }
        
        std::string ToString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << GetWindowWidth() << ", " << GetWindowHeight();
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppTickEvent : public Event {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class AppRenderEvent : public Event {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}
