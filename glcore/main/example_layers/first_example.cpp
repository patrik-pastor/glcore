//
// Created by shepherd on 9.4.23.
//

#include <glcore/main/example_layers/first_example.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

namespace glcore {

FirstExample::FirstExample() : camera_controller_(16.0f / 9.0f) {}

void FirstExample::OnAttach() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader_ = CreateRef<Shader>("assets/GLSL/first_example.glsl");

    glGenVertexArrays(1, &quad_va_);
    glBindVertexArray(quad_va_);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f
    };

    glGenBuffers(1, &quad_vb_);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vb_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    glGenBuffers(1, &quad_ib_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_ib_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void FirstExample::OnDetach() {
    glDeleteVertexArrays(1, &quad_va_);
    glDeleteBuffers(1, &quad_vb_);
    glDeleteBuffers(1, &quad_ib_);
}

void FirstExample::OnEvent(Event& event) {
    camera_controller_.OnEvent(event);
    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent& e) {
        square_color_ = square_alternate_color_;
        return false;
    });

    dispatcher.Dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent& e) {
        square_color_ = square_base_color_;
        return false;
    });
}

void FirstExample::OnUpdate(float delta_time) {
    camera_controller_.OnUpdate(delta_time);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_->Bind();
    shader_->SetMat4("u_view_projection", camera_controller_.GetCamera().GetViewProjectionMatrix());
    shader_->SetVec4("u_color", square_color_);

    glBindVertexArray(quad_va_);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void FirstExample::OnImguiRender() {
    ImGui::Begin("Controls");
    if (ImGui::ColorEdit4("Sqaure Base Color", glm::value_ptr(square_base_color_))) {
      square_color_ = square_base_color_;
    }
    ImGui::ColorEdit4("Sqaure Alternate Color", glm::value_ptr(square_alternate_color_));
    ImGui::End();
}

} // glcore