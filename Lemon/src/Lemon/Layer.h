#pragma once
#include "lmpch.h"
#include "Core.h"
#include "Lemon/Events/Event.h"

namespace Lemon
{
    class LEMON_API Layer {
    protected:
        std::string m_DebugName;
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& e) {}

        inline const std::string& GetName() { return m_DebugName; }
    };
}
