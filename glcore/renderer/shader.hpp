//
// Created by shepherd on 8.4.23.
//

#ifndef GLCORE_SHADER_HPP
#define GLCORE_SHADER_HPP

#include <string>

#include <glm/glm.hpp>

namespace glcore {

class Shader {
public:
    explicit Shader(const std::string& filepath);

    void Bind() const;

    void SetInt(const std::string& name, int value) const;

    void SetFloat(const std::string& name, float value) const;

    void SetVec3(const std::string& name, const glm::vec3& vec) const;

    void SetVec4(const std::string& name, const glm::vec4& vec) const;

    void SetMat4(const std::string& name, const glm::mat4& mat) const;

private:
    static void CheckCompileErrors(uint32_t shader_id, const std::string& type, const std::string& filepath);

    uint32_t id_;
};

} // glcore

#endif //GLCORE_SHADER_HPP
