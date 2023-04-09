//
// Created by shepherd on 8.4.23.
//

#include <glcore/renderer/shader.hpp>

#include <iostream>
#include <fstream>
#include <sstream>

#include <glad/glad.h>

namespace glcore {

void Shader::CheckCompileErrors(uint32_t shader_id, const std::string& type, const std::string& filepath) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader_id, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER::COMPILATION_ERROR of type: " << type << '\n' << infoLog << "filepath: " << filepath;
        }
    } else {
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_id, 1024, nullptr, infoLog);
            std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << '\n' << infoLog << "filepath: " << filepath;
        }
    }
}

Shader::Shader(const std::string& filepath) {
    // 1. divide vertex and fragment part
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#type") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            } else {
                std::cerr << "Unknown shader: " << line;
            }
        } else {
            if (type == ShaderType::NONE) {
                std::cerr << "No shader defined";
            } else {
                ss[(int) type] << line << '\n';
            }
        }
    }
    std::string vertex_code = ss[(int) ShaderType::VERTEX].str();
    std::string fragment_code = ss[(int) ShaderType::FRAGMENT].str();

    // 2. convert, compile and link sources to shader program
    // 2.1 convert string to c str
    const char *vertex_str = vertex_code.c_str();
    const char *fragment_str = fragment_code.c_str();
    // 2.2.1 vertex shader
    uint32_t vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vertex_str, nullptr);
    glCompileShader(vertex_id);
    CheckCompileErrors(vertex_id, "VERTEX", filepath);
    // 2.2.2 fragment shader
    uint32_t fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &fragment_str, nullptr);
    glCompileShader(fragment_id);
    CheckCompileErrors(fragment_id, "FRAGMENT", filepath);
    // 2.3 shader program
    id_ = glCreateProgram();
    glAttachShader(id_, vertex_id);
    glAttachShader(id_, fragment_id);
    glLinkProgram(id_);
    CheckCompileErrors(id_, "PROGRAM", filepath);
    // 2.4 delete the shaders as they're linked into program and no longer necessary
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

void Shader::Bind() const {
    glUseProgram(id_);
}

void Shader::SetInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetIntArray(const std::string& name, int *values, int count) {
    glUniform1iv(glGetUniformLocation(id_, name.c_str()), count, values);
}

void Shader::SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::SetVec4(const std::string& name, const glm::vec4& vec) const {
    glUniform4f(glGetUniformLocation(id_, name.c_str()), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetVec3(const std::string& name, const glm::vec3& vec) const {
    glUniform3f(glGetUniformLocation(id_, name.c_str()), vec.x, vec.y, vec.z);
}

void Shader::SetMat4(const std::string& name, const glm::mat4& mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

} // glcore