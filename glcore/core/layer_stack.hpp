//
// Created by shepherd on 9.3.23.
//

#ifndef GLCORE_LAYER_STACK_HPP
#define GLCORE_LAYER_STACK_HPP

#include <vector>

#include <glcore/core/layer.hpp>

namespace glcore {

class LayerStack {
public:
    LayerStack() = default;

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *overlay);

    std::vector<Layer *>::iterator begin();

    std::vector<Layer *>::iterator end();

    std::vector<Layer *>::const_iterator begin() const;

    std::vector<Layer *>::const_iterator end() const;

private:
    std::vector<Layer *> layers_;
    int layer_insert_index_ = 0;
};

} // glcore

#endif //GLCORE_LAYER_STACK_HPP
