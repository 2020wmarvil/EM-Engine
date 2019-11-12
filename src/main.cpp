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
#include "Terrain.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Collider.h"

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

	// GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	// const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	// GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "My Title", monitor, NULL);

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

	// load sprites
	Player player("../res/sprites/hero.png", 3, 8,
		glm::vec3(0.0f, 200.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Terrain floor("../res/sprites/floor.png", 1, 1,
		glm::vec3(0.0f, 0.0f, 0.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	Terrain wall("../res/sprites/wall.png", 1, 1,
		glm::vec3(775.0f, 300.0f, 0.0f), 90.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	std::vector<const Entity*> entities = { &player, &floor, &wall };
	Collider collider(&entities);	// collisions must effect both the position, velocity, and momentum of the object

	// create camera
	Camera camera(&player, WIDTH/2, HEIGHT/2);

	// create shader
	Shader shader("../res/shaders/vert.glsl", "../res/shaders/frag.glsl");
	shader.Bind();

	std::cout << "Error code: " << glGetError() << std::endl;

	double lasttime = glfwGetTime();

	float lastTime = glfwGetTime();

	while(!glfwWindowShouldClose(window)) {
  		float current = glfwGetTime();
  		float elapsed = current - lastTime;

		processInput(window, player);

		// update the world	- this should be done cleaner, maybe one update call that updates the whole scene?
		player.Update(elapsed);
		std::vector<int> collisions = collider.Collide(&player);
		for (int collision : collisions) {
			std::cout << collision << " ";
		} std::cout << std::endl;

		// update the MVP matrices
		glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, -1.0f, 1.0f);  
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 vp = projection * view;

		// prepare for rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		// render opaque textures
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
		// now render transparent textures from back to front
		wall.Draw(shader, &vp);
		floor.Draw(shader, &vp);
		player.Draw(shader, &vp);
		glDisable(GL_BLEND);

		// swap the buffers and poll for events
	 	glfwSwapBuffers(window);
		glfwPollEvents();

		// cap the framerate
	    while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
	    } lasttime += 1.0/TARGET_FPS;

		// error checking
		if (int e=glGetError() != 0) { std::cout << "OpenGL Error: " << e << std::endl; }

  		lastTime = current;
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
