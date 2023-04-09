//
// Created by shepherd on 29.3.23.
//

#include <glcore/renderer/orthographic_camera_controller.hpp>

#include <glcore/core/input.hpp>
#include <glcore/core/key_codes.hpp>

namespace glcore {

OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation) :
        aspect_ratio_(aspect_ratio),
        rotation_(rotation),
        camera_(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_) {

}

void OrthographicCameraController::OnUpdate(float delta_time) {
// CAMERA TRANSLATION
    if (Input::IsKeyPressed(KEY_A)) {
        camera_position_.x -= camera_translation_speed_ * delta_time;
    } else if (Input::IsKeyPressed(KEY_D)) {
        camera_position_.x += camera_translation_speed_ * delta_time;
    }
    if (Input::IsKeyPressed(KEY_W)) {
        camera_position_.y += camera_translation_speed_ * delta_time;
    } else if (Input::IsKeyPressed(KEY_S)) {
        camera_position_.y -= camera_translation_speed_ * delta_time;
    }

    // CAMERA ROTATION
    if (rotation_) {
        if (Input::IsKeyPressed(KEY_Q)) {
            camera_rotation_ += camera_rotation_speed_ * delta_time;
        }
        if (Input::IsKeyPressed(KEY_E)) {
            camera_rotation_ -= camera_rotation_speed_ * delta_time;
        }

        camera_.SetRotation(camera_rotation_);
    }

    camera_.SetPosition(camera_position_);

    camera_translation_speed_ = zoom_level_;
}

void OrthographicCameraController::OnEvent(Event& event) {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& event) {
    zoom_level_ -= event.GetYoffset() * 0.25f;
    zoom_level_ = std::max(zoom_level_, 0.25f);
    camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);

    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& event) {
    aspect_ratio_ = (float) event.GetWidth() / (float) event.GetHeight();
    camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);

    return false;
}

const OrthographicCamera& OrthographicCameraController::GetCamera() const {
    return camera_;
}

} // glcore