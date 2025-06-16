#include "cursor_pos_callback.hpp"

// Function that will be called every time the user moves the mouse while the application has focus.
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
	// Do not process mouse movement at all when the logo mode is turned on.
	if (logoModeTurnedOn)
	{
		return;
	}

	// Change cursors only when the orthogonal projection mode is turned on.
	if (orthogonalProjectionTurnedOn)
	{
		// REFERENCE: https://www.glfw.org/docs/3.3/input_guide.html#cursor_set
		// If the mouse cursor is positioned above the freezing chamber, turn it to a blue snowflake.
		if (xpos >= 0.26875 * windowWidth && xpos <= 0.73 * windowWidth 
			&& ypos >= 0.393333 * windowHeight && ypos <= 0.603333 * windowHeight)
		{
			glfwSetCursor(window, blueSnowflakeCursor);
		}
		// Otherwise, reset the mouse cursor to the default arrow one.
		else
		{
			glfwSetCursor(window, NULL);
		}

		return;
	}

	// Calculate "camera's front" vector that acts as insurance that however the user moves the camera, it will always
	// keep looking straight ahead.
	// Math is explained below. In 2. thing needed to manually create the LookAt matrix - "camera's direction":
	// glm::vec3 cameraTarget = cameraPosition + cameraFront;
	// glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget) = glm::normalize(-cameraFront);

	// 0. step: if the mouse input is received for the first time, the previous cursor position should be set to the
	// position in which the user entered the application's window. Offsets should be calculated based on that position
	// of mentry. Wihout this added step, the camera would suddenly jump to the position of the entry with mouse, which
	// is usually far away from the window's center.
	float xPos = static_cast<float>(xpos);
	float yPos = static_cast<float>(ypos);
	if (firstMouseEntry)
	{
		previousCursorPosX = xPos;
		previousCursorPosY = yPos;
		firstMouseEntry = false;
	}

	// 1. step: calculate the mouse cursor's offset since the last frame.
	float xOffset = xPos - previousCursorPosX;
	// The order of subtraction is reversed, because the y-coordinates range from the bottom to the top.
	float yOffset = previousCursorPosY - yPos;
	previousCursorPosX = xPos;
	previousCursorPosY = yPos;

	// 2. step onward: done in the "Camera" class.
	camera->processMovementOfMouse(xOffset, yOffset);
}
