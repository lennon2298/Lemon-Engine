#pragma once

#include "lmpch.h"
#include "Core.h"
#include "Layer.h"

namespace Lemon {
    class LEMON_API LayerStack {
    private:
        std::vector<Layer*> m_Layers;
        std::vector<Layer*>::iterator m_LayerInsert;

    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);
        void PushOverlay(Layer* overlay);
        void PopOverlay(Layer* overlay);

        inline std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        inline std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    };
}
