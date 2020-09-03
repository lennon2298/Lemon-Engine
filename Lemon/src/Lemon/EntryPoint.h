#pragma once
#include "Log.h"

extern Lemon::Application* Lemon::CreateApplication();

int main(int argc, char** argv) {
    Lemon::Log::Init();
    LM_CORE_WARN("Ayy lmao");
    LM_INFO("Fuck this shit");

    std::cout << "Welcome to Lemon Engine, A rip-off of Hazel Engine" << std::endl;
    auto app = Lemon::CreateApplication();
    app->Run();
    delete app;
}
