//
// Created by shepherd on 20.3.23.
//

#include <glcore/core/linux_window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glcore/core/log.hpp>
#include <glcore/events/application_event.hpp>
#include <glcore/events/key_event.hpp>
#include <glcore/events/mouse_event.hpp>

namespace glcore {

static int window_count = 0;

LinuxWindow::LinuxWindow(const WindowProps& props){
    LOG_CORE_INFO("Creating window_ {0} ({1}, {2})", props.title, props.width, props.height);
    data_.title = props.title;
    data_.width = props.width;
    data_.height = props.height;

    if(window_count == 0){
        if(glfwInit() == GLFW_FALSE) {
            LOG_CORE_CRITICAL("failed to initialized glfw");
        } else {
            LOG_CORE_TRACE("glfwInit");
        }
    }

    window_ = glfwCreateWindow(data_.width, data_.height, data_.title.c_str(), nullptr, nullptr);
    if(window_ == nullptr){
        LOG_CORE_CRITICAL("failed to create GLFW window_");
    } else {
        LOG_CORE_TRACE("glfwCreateWindow");
    }
    ++window_count;

    glfwMakeContextCurrent(window_);
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow *_, int width, int height) {
        glViewport(0, 0, width, height);
    });

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        LOG_CORE_CRITICAL("failed to initialize GLAD");
    } else {
        LOG_CORE_TRACE("gladLoadGLLoader");
    }

    LOG_CORE_INFO("OpenGL Info:");
    LOG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    LOG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

    glfwSetWindowUserPointer(window_, &data_);
    SetVSync(true);

    glfwSetWindowSizeCallback(window_, [](GLFWwindow *window, int width, int height) {
        WindowData data = *(WindowData *) glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.event_callback(event);
    });

    glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.event_callback(event);
    });

    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, false);
                data.event_callback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.event_callback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, true);
                data.event_callback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(window_, [](GLFWwindow *window, uint32_t codepoint) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        KeyTypedEvent event(codepoint);
        data.event_callback(event);
    });

    glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int mods) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.event_callback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.event_callback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window_, [](GLFWwindow *window, double xoffset, double yoffset) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        MouseScrolledEvent event(xoffset, yoffset);
        data.event_callback(event);
    });

    glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double xpos, double ypos) {
        WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
        MouseMovedEvent event(xpos, ypos);
        data.event_callback(event);
    });
}

void LinuxWindow::OnUpdate() {
    glfwSwapBuffers(window_);
    glfwPollEvents();
}

int LinuxWindow::GetWidth() const {
    return data_.width;
}

int LinuxWindow::GetHeight() const {
    return data_.height;
}

void *LinuxWindow::GetNativeWindow() const {
    return window_;
}

void LinuxWindow::SetEventCallback(const Window::EventCallbackFn& callback) {
    data_.event_callback = callback;
}

void LinuxWindow::SetVSync(bool enabled) {
    if(enabled){
        glfwSwapInterval(1);
    } else {
        glfwSwapInterval(0);
    }
    data_.vsync = enabled;
}

} // glcore