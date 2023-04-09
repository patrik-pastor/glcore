//
// Created by shepherd on 23.3.23.
//

#ifndef GLCORE_ORTHOGRAPHIC_CAMERA_HPP
#define GLCORE_ORTHOGRAPHIC_CAMERA_HPP

#include <glm/glm.hpp>

namespace glcore {

class OrthographicCamera {
public:
    OrthographicCamera(float left, float right, float bottom, float top);

    const glm::vec3& GetPosition() const;

    void SetPosition(const glm::vec3& position);

    float GetRotation() const;

    void SetRotation(float rotation);

    void SetProjection(float left, float right, float bottom, float top);

    const glm::mat4& GetProjectionMatrix() const;

    const glm::mat4& GetViewMatrix() const;

    const glm::mat4& GetViewProjectionMatrix() const;

private:
    void RecalculateViewMatrix();

    glm::mat4 projection_matrix_;
    glm::mat4 view_matrix_;
    glm::mat4 view_projection_matrix_;
    glm::vec3 position_ = {0.0f, 0.0f, 0.0f};
    float rotation_ = 0.0f;
};

} // glcore

#endif //GLCORE_ORTHOGRAPHIC_CAMERA_HPP
