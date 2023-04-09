//
// Created by shepherd on 21.3.23.
//

#ifndef GLCORE_IMGUI_LAYER_HPP
#define GLCORE_IMGUI_LAYER_HPP

#include <glcore/core/layer.hpp>

namespace glcore {

class ImguiLayer : public Layer {
public:
    ImguiLayer();

    void OnAttach() override;

    void OnDetach() override;

    void Begin();

    void End();

};

} // glcore

#endif //GLCORE_IMGUI_LAYER_HPP
