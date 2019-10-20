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
#include "Entity.h"
#include "Shader.h"
#include "SpriteLoader.h"
#include "SpriteData.h"

// constants
#define WIDTH 1920
#define HEIGHT 1080
#define TARGET_FPS 600

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

	// load sprites
	SpriteLoader loader;
	Entity square(loader.LoadSprite("../res/sprites/square.ems"));

	// create the shader
	Shader shader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");

	// set initial uniforms
	shader.Bind();	
	shader.SetUniformVec4f("u_Color", glm::vec4(0.8f, 0.25f, 0.4f, 1.0f));
//	glm::mat4 transform = glm::mat4(1.0f);
//	shader.SetUniformMat4f("u_Transform2",transform);
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
		shader.Bind();
		square.Bind();

		// update uniforms
		shader.Bind();
		shader.SetUniformVec3f("u_Transform", glm::vec3(sin(glfwGetTime())/2, cos(glfwGetTime())/2, 0.0f));
		glm::mat4 Model = glm::mat4(1.0f);
		Model = glm::translate(Model,glm::vec3(sin(glfwGetTime())/2,cos(glfwGetTime())/2,0.0f));
		shader.SetUniformMat4f("u_Model",Model);
		shader.SetUniformMat4f("u_View",glm::mat4(1.0f));
		shader.SetUniformMat4f("u_Projection",glm::mat4(1.0f));
		// render
		//glDrawElements(GL_TRIANGLES, indices.size()*sizeof(unsigned int)/3, GL_UNSIGNED_INT, nullptr);
		glDrawElements(GL_TRIANGLES, 6*sizeof(unsigned int)/3, GL_UNSIGNED_INT, nullptr);

		// swap the buffers and poll for events
	 	glfwSwapBuffers(window);
		glfwPollEvents();

		// cap the framerate
	    while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	    } lasttime += 1.0/TARGET_FPS;

		// error checking
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
