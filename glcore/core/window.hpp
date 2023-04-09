//
// Created by shepherd on 20.3.23.
//

#ifndef GLCORE_WINDOW_HPP
#define GLCORE_WINDOW_HPP

#include <string>
#include <functional>

#include <glcore/core/core.hpp>
#include <glcore/events/event.hpp>

namespace glcore {

struct WindowProps {
    std::string title;
    int width;
    int height;

    explicit WindowProps(const std::string& title = "glcore", int width = 1280, int height = 720);
};

class Window {
public:
    using EventCallbackFn = std::function<void(Event&)>;

    static Scope<Window> Create(const WindowProps& props = WindowProps());

    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual int GetWidth() const = 0;

    virtual int GetHeight() const = 0;

    virtual void SetVSync(bool enabled) = 0;

    virtual void *GetNativeWindow() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
};

} // glcore

#endif //GLCORE_WINDOW_HPP
