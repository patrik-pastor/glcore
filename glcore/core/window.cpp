//
// Created by shepherd on 20.3.23.
//

#include <glcore/core/window.hpp>
#include <glcore/core/linux_window.hpp>

namespace glcore {

WindowProps::WindowProps(const std::string& title, int width, int height) : title(title), width(width),
                                                                            height(height) {}

Scope<Window> Window::Create(const WindowProps& props) {
    return CreateScope<LinuxWindow>(props);
}

} // glcore