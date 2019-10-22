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
#include "Player.h"
#include "Camera.h"
#include "Renderer.h"
#include "Shader.h"
#include "SpriteLoader.h"
#include "SpriteData.h"

// constants
#define WIDTH 1920
#define HEIGHT 1080
#define TARGET_FPS 600

void processInput(GLFWwindow *window, Player& player);
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
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	Player player(loader.LoadSprite("../res/sprites/player.ems"), 
		glm::vec3(400.0f, 500.0f, 0.0f), 0.0f, glm::vec3(0.5f, 0.5f, 0.5f));
	Entity floor(loader.LoadSprite("../res/sprites/floor.ems"), 
		glm::vec3(400.0f, 300.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	// create camera
	Camera camera(&player, WIDTH/2, HEIGHT/2);

	// create shader
	Shader shader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");

	// create renderer
	Renderer renderer;

	std::cout << "Error code: " << glGetError() << std::endl;

	double lasttime = glfwGetTime();

	while(!glfwWindowShouldClose(window)) {
		processInput(window, player);

		// update the world	- this should be done cleaner, maybe one update call that updates the whole scene?
		player.Update();
		floor.Update();

		// update the MVP matrices
		glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);  
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 vp = projection * view;

		// prepare for rendering
		renderer.Clear();

		// update shader and render player
		{
			shader.Bind();

			glm::mat4 model = player.ComputeModel();
			glm::mat4 mvp = vp * model;

			shader.SetUniformMat4f("u_MVP", mvp);
			shader.SetUniformVec4f("u_Color", glm::vec4(0.8f, 0.25f, 0.4f, 1.0f));

			player.Bind();
			renderer.Draw(player, shader);
		}

		// update shader and render floor
		{
			shader.Bind();

			glm::mat4 model = floor.ComputeModel();
			glm::mat4 mvp = vp * model;

			shader.SetUniformMat4f("u_MVP", mvp);
			shader.SetUniformVec4f("u_Color", glm::vec4(0.54f, 0.27f, 0.07f, 1.0f));

			floor.Bind();
			renderer.Draw(floor, shader);
		}

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
 
void processInput(GLFWwindow *window, Player& player) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
	}

	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		player.ScaleVelocityX(1);
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		player.ScaleVelocityX(-1);
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		player.ScaleVelocityY(1);
	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		player.ScaleVelocityY(-1);
	
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE) {
		player.ScaleVelocityX(0);
	}
	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
		player.ScaleVelocityY(0);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
