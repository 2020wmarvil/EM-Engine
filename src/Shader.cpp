#include "Shader.h"

#include <GL/glew.h>

#include <sstream>
#include <fstream>

Shader::Shader(const std::string& vsFilepath, const std::string& fsFilepath)
    : m_RendererID(0), m_VertexFilepath(vsFilepath), m_FragmentFilepath(fsFilepath) 
{
	ShaderProgramSource source = ParseShader(vsFilepath, fsFilepath);
	m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader() {
    glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& vsFilepath, const std::string& fsFilepath) {
	std::string line;
	std::stringstream ss[2];

	std::ifstream vsStream(vsFilepath);
	while (getline(vsStream, line)) {
		ss[0] << line << "\n";
	}

	std::ifstream fsStream(fsFilepath);
	while (getline(fsStream, line)) {
		ss[1] << line << "\n";
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();

	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;

		glDeleteShader(id);

		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const {
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniformVec2f(const std::string& name, const glm::vec2& vec) {
	glUniform2f(GetUniformLocation(name), vec.x, vec.y);
}

void Shader::SetUniformVec3f(const std::string& name, const glm::vec3& vec) {
	glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
}

void Shader::SetUniformVec4f(const std::string& name, const glm::vec4& vec) {
	glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

int Shader::GetUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());

    if (location == -1)
        std::cout << "Warning, uniform " << name << " doesn't exist!" << std::endl;
	
	m_UniformLocationCache[name] = location;
    
    return location;
}