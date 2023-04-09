//
// Created by shepherd on 20.3.23.
//

#ifndef GLCORE_LINUX_WINDOW_HPP
#define GLCORE_LINUX_WINDOW_HPP

#include <glcore/core/window.hpp>

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace glcore {

class LinuxWindow : public Window {
public:
    explicit LinuxWindow(const WindowProps& props);

    ~LinuxWindow() override = default;

    void OnUpdate() override;

    int GetWidth() const override;

    int GetHeight() const override;

    void SetVSync(bool enabled) override;

    void *GetNativeWindow() const override;

    void SetEventCallback(const EventCallbackFn& callback) override;
private:
    GLFWwindow *window_;

    struct WindowData {
        std::string title;
        int width;
        int height;
        bool vsync;
        EventCallbackFn event_callback;
    } data_;
};

} // glcore

#endif //GLCORE_LINUX_WINDOW_HPP
