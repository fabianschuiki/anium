/* Copyright (c) 2014 Fabian Schuiki */
#include <GLFW/glfw3.h>
#include <cairo/cairo.h>
#include <anium/window.hpp>
#include <anium/stack.hpp>
#include <anium/button.hpp>
#include <anium/renderer.hpp>
#include <iostream>

using namespace gamma::convenience;

static void gl_prepare_draw(GLFWwindow* window)
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char** argv)
{
	// Initialize GLFW
	if (!glfwInit()) {
		std::cerr << "unable to initialize GLFW\n";
		return 1;
	}

	// Create a windowed mode.
	GLFWwindow* window = glfwCreateWindow(640, 480, "anium interactive", NULL, NULL);
	if (!window) {
		std::cerr << "unable to create window\n";
		glfwTerminate();
		return 1;
	}

	// Make the window's OpenGL context current.
	glfwMakeContextCurrent(window);

	// Create a user interface hierarchy.
	anium::window::ptr aw(new anium::window);
	anium::stack::ptr as(new anium::stack);
	aw->content = as;
	anium::button::ptr ab0(new anium::button);
	anium::button::ptr ab1(new anium::button);
	as->subviews.push_back(ab0);
	as->subviews.push_back(ab1);

	aw->position = vector2f(100,100);
	aw->size = vector2f(200,200);

	// Initialize the renderer.
	anium::renderer::ptr rndr = anium::renderer::make(aw);

	// Enter and stay in the main loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		gl_prepare_draw(window);

		glPushAttrib(GL_CURRENT_BIT);
		rndr->draw();
		glPopAttrib();

		// Swap buffers and wait for events.
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}