//
// Created by shepherd on 8.3.23.
//

#include <glcore/events/application_event.hpp>

#include <sstream>

namespace glcore {

WindowResizeEvent::WindowResizeEvent(int width, int height) : width_(width), height_(height) {}

std::string WindowResizeEvent::ToString() const {
    std::stringstream ss;
    ss << "WindowResizeEvent: " << width_ << ", " << height_;
    return ss.str();
}

int WindowResizeEvent::GetWidth() const {
    return width_;
}

int WindowResizeEvent::GetHeight() const {
    return height_;
}

} // glcore