#include "scroll_callback.hpp"

// Function that will be called every time the user scrolls the mouse's middle button.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (orthogonalProjectionTurnedOn)
	{
		return;
	}

	camera->processMouseScroll(static_cast<float>(yoffset));
}
