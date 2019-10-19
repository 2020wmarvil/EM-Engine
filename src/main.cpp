// external imports
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

// standard library imports
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

// our library imports

// constants
#define WIDTH 1920
#define HEIGHT 1080
#define TARGET_FPS 600

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

ShaderProgramSource ParseShader(const std::string& vsFilepath, const std::string& fsFilepath);
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

int main() {
	// glfw setup
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	glfwSetWindowTitle(window, "EM Engine");
	glfwSetWindowAspectRatio(window, WIDTH, HEIGHT);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// opengl setup
	if (glewInit() != GLEW_OK) {
		std::cout << "ERROR: cannot initialize glew" << std::endl;
		exit(1);
	}

	glViewport(0, 0, WIDTH, HEIGHT);

	glEnable(GL_DEPTH_TEST);  
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// object data 
	float positions[] = { 
		-0.5f,  0.5f,
		 0.5f,  0.5f,
		 0.5f, -0.5f,
		-0.5f, -0.5f
	};

	unsigned int indices[] {
		0, 1, 2,
		0, 2, 3
	};

	// create the vertex objects
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8, (const void*)0);

	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	// create the shader
	std::string vsFilepath = "../res/shaders/lamp/lamp_VS.glsl";
	std::string fsFilepath = "../res/shaders/lamp/lamp_FS.glsl";
	ShaderProgramSource source = ParseShader(vsFilepath, fsFilepath);
	unsigned int shader = CreateShader(source.vertexSource, source.fragmentSource);
//	uniforms.push_back(glGetUniformLocation(shader,in.c_str()));
//	glUniform4f(uniforms[id],a,b,c,d);

	std::cout << "Error code: " << glGetError() << std::endl;

	double lasttime = glfwGetTime();

	// game loop
	while(!glfwWindowShouldClose(window)) {
		// input
		processInput(window);

		// clear the buffers
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// bind everything
		glUseProgram(shader);
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

		// render
		glDrawElements(GL_TRIANGLES, sizeof(indices)/3, GL_UNSIGNED_INT, nullptr);

		// swap the buffers and poll for events
	 	glfwSwapBuffers(window);
		glfwPollEvents();

		// cap the framerate
	    while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	    } lasttime += 1.0/TARGET_FPS;

		if (int e=glGetError() != 0) { std::cout << "OpenGL Error: " << e << std::endl; }
	}

	// terminate glfw
    glfwDestroyWindow(window);
    glfwTerminate();

	return 0;
}
 
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

ShaderProgramSource ParseShader(const std::string& vsFilepath, const std::string& fsFilepath) {
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

unsigned int CompileShader(unsigned int type, const std::string& source) {
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
	} return id;
}

unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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
/*
void Shader::SetUniform1i(const std::string& name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value) {
    glUniform1f(GetUniformLocation(name), value);
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

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	*/