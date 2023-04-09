//
// Created by shepherd on 9.4.23.
//

#ifndef GLCORE_FIRST_EXAMPLE_HPP
#define GLCORE_FIRST_EXAMPLE_HPP

#include <glm/glm.hpp>

#include <glcore/core/layer.hpp>
#include <glcore/renderer/orthographic_camera_controller.hpp>
#include <glcore/renderer/shader.hpp>

namespace glcore {

class FirstExample : public Layer {
public:
    FirstExample();

    void OnAttach() override;

    void OnDetach() override;

    void OnEvent(Event& event) override;

    void OnUpdate(float delta_time) override;

    void OnImguiRender() override;

private:
    OrthographicCameraController camera_controller_;
    Ref<Shader> shader_;

    uint32_t quad_va_, quad_vb_, quad_ib_;
    glm::vec4 square_base_color_ = {0.8f, 0.2f, 0.3f, 1.0f};
    glm::vec4 square_alternate_color_ = {0.2f, 0.3f, 0.8f, 1.0f};
    glm::vec4 square_color_ = square_base_color_;
};

} // glcore

#endif //GLCORE_FIRST_EXAMPLE_HPP
