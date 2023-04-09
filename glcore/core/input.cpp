//
// Created by shepherd on 23.3.23.
//

#include <glcore/core/input.hpp>

#include <GLFW/glfw3.h>

#include <glcore/core/application.hpp>

namespace glcore {

bool Input::IsKeyPressed(int keycode) {
    auto *window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS;
}

} // glcore