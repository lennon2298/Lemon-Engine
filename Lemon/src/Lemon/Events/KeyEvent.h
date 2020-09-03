#pragma once

#include "Event.h"

namespace Lemon {
    class LEMON_API KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keycode) 
        : m_KeyCode(keycode) {}

        int m_KeyCode;
    };

    class LEMON_API KeyPressedEvent : public KeyEvent {
    private:
        int m_RepeatCount;
    public:
        KeyPressedEvent(int keycode, int repeatcount) 
        : KeyEvent(keycode), m_RepeatCount(repeatcount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressed: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class LEMON_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::stringstream ss;
            ss << "Key Released: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
};
