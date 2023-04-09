//
// Created by shepherd on 9.3.23.
//

#ifndef GLCORE_LAYER_HPP
#define GLCORE_LAYER_HPP

#include <string>

#include <glm/glm.hpp>

#include <glcore/events/event.hpp>
#include <glcore/events/key_event.hpp>

namespace glcore {

class Layer {
public:
    explicit Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach() {}

    virtual void OnDetach() {}

    virtual void OnUpdate(float delta_time) {}

    virtual void OnImguiRender() {}

    virtual void OnEvent(Event& event) {}

private:
    std::string name_;
};

} // glcore

#endif //GLCORE_LAYER_HPP
