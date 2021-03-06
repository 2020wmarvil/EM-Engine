#pragma once

#include <string>
#include <unordered_map>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
    unsigned int m_RendererID;
    std::string m_VertexFilepath, m_FragmentFilepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(const std::string& vsFilepath, const std::string& fsFilepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniformVec2f(const std::string& name, const glm::vec2& vec);
    void SetUniformVec3f(const std::string& name, const glm::vec3& vec);
    void SetUniformVec4f(const std::string& name, const glm::vec4& vec);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    ShaderProgramSource ParseShader(const std::string& vsFilepath, const std::string& fsFilepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

    int GetUniformLocation(const std::string& name);
};