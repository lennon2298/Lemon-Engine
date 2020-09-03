#include "lmpch.h"
#include "Lemon.h"

class ExampleLayer : public Lemon::Layer {
    public:
    ExampleLayer()
    :Layer("New Layer") {}

    void OnUpdate() override {
        LM_TRACE("ExampleLayer::Update");
    }

    void OnEvent(Lemon::Event& e) override {
        LM_INFO("{0}", e);
    }
};

class Sandbox : public Lemon::Application {
    public:
    Sandbox(){
        PushLayer(new ExampleLayer());
    }

    ~Sandbox(){

    }
};

Lemon::Application* Lemon::CreateApplication() {
    return new Sandbox();
}
