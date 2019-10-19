#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "ryangl.h"
#include <math.h>
int main(void)
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window){
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	if (GLEW_OK != err){
		/* Problem: glewInit failed, something is seriously wrong. */
		printf("Error: %s\n", glewGetErrorString(err));
	}
	printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	/* Loop until the user closes the window */
	ryangl::object a({-.5,.5,0,.5,0,0,-.5,0},{0,1,2,0,2,3},2,{"vertex.shader","fragment.shader"});
	int move = a.newUniform("move");
	float it = 0;
	while (!glfwWindowShouldClose(window)){
		it=it+.001;
		glClear(GL_COLOR_BUFFER_BIT);
		/* Swap front and back buffers */
		a.setUniform(move,sin(5*it),cos(5*it),0,0);
		a.draw();
		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
