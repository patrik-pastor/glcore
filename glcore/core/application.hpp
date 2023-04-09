//
// Created by shepherd on 20.3.23.
//

#ifndef GLCORE_APPLICATION_HPP
#define GLCORE_APPLICATION_HPP

#include <glcore/core/window.hpp>
#include <glcore/core/layer_stack.hpp>
#include <glcore/events/event.hpp>
#include <glcore/events/application_event.hpp>
#include <glcore/imgui/imgui_layer.hpp>

namespace glcore {

class Application {
public:
    Application();

    void Run();

    void OnEvent(Event& e);

    bool IsRunning() const;

    void SetRunning(bool running);

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *layer);

    static Application& GetInstance();

    Window &GetWindow() const;

private:
    static Application *application_instance_;

    bool OnWindowClose(WindowCloseEvent& e);

    Scope<Window> window_;
    bool running_ = true;
    LayerStack layer_stack_;
    ImguiLayer *imgui_layer_;
    float last_time_ = 0.0f;
};

} // glcore

#endif //GLCORE_APPLICATION_HPP
