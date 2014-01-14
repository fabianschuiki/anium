/* Copyright (c) 2014 Fabian Schuiki */
#include <GLFW/glfw3.h>
#include <cairo/cairo.h>
#include <iostream>

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

	// Enter and stay in the main loop until the user closes the window.
	while (!glfwWindowShouldClose(window))
	{
		gl_prepare_draw(window);

		glPushAttrib(GL_CURRENT_BIT);
		glColor3f(1,1,1);
		glBegin(GL_TRIANGLES);
		glVertex2f(100,100);
		glVertex2f(100,200);
		glVertex2f(200,200);
		glEnd();
		glPopAttrib();

		// Swap buffers and wait for events.
		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}