//
// Created by shepherd on 20.3.23.
//

#include <glcore/core/application.hpp>

#include <GLFW/glfw3.h>

#include <glcore/core/log.hpp>

namespace glcore {

Application *Application::application_instance_ = nullptr;

Application::Application() {
    INIT_LOG();

    if (application_instance_ != nullptr) {
        LOG_CORE_CRITICAL("Application already exists!");
    }
    application_instance_ = this;

    window_ = Window::Create();
    window_->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    imgui_layer_ = new ImguiLayer();
    PushOverlay(imgui_layer_);
}

void Application::Run() {
    while (IsRunning()) {
        float time = glfwGetTime();
        float delta_time = time - last_time_;
        last_time_ = time;

        for (Layer *layer: layer_stack_) {
            layer->OnUpdate(delta_time);
        }

        imgui_layer_->Begin();
        for (Layer *layer: layer_stack_)
            layer->OnImguiRender();
        imgui_layer_->End();

        window_->OnUpdate();
    }
}

void Application::OnEvent(Event& e) {
    LOG_CORE_INFO(e.ToString());
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    for (auto it = layer_stack_.end(); it != layer_stack_.begin();) {
        (*--it)->OnEvent(e);
        if (e.handled_) {
            break;
        }
    }
}

bool Application::IsRunning() const {
    return running_;
}

void Application::SetRunning(bool running) {
    running_ = running;
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    SetRunning(false);
    return true;
}

void Application::PushLayer(Layer *layer) {
    layer_stack_.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer) {
    layer_stack_.PushOverlay(layer);
    layer->OnAttach();
}

Application& Application::GetInstance() {
    return *application_instance_;
}

Window& Application::GetWindow() const {
    return *window_;
}

} // glcore