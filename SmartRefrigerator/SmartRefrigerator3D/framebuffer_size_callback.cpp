#include "framebuffer_size_callback.hpp"

// Function that will be called every time the application's window changes size.
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, width, height);
}
