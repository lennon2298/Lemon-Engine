#include "lmpch.h"
#include "Lemon.h"

class Sandbox : public Lemon::Application {
    public:
    Sandbox(){

    }

    ~Sandbox(){

    }
};

Lemon::Application* Lemon::CreateApplication() {
    return new Sandbox();
}
