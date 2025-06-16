#include "mouse_button_callback.hpp"

// Function that processes clicking on mouse buttons.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// Do not process mouse clicks at all if any mouse button other than the left one is pressed.
	if (!(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS))
	{
		return;
	}

	if (logoModeTurnedOn)
	{
		logoModeTurnedOn = false;
		graphicalModeTurnedOn = true;
		// Initialize the graphical mode activation timestamp with the current time.
		timeWhenGraphicalModeWasActivated = static_cast<float>(glfwGetTime());
		if (!orthogonalProjectionTurnedOn)
		{
			// Tell the GLFW library to capture and hide the mouse cursor. Capturing the mouse cursor means fixating
			// it to the center of the application's window and only letting it move if the application loses focus
			// or quits.
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		return;
	}

	if (graphicalModeTurnedOn)
	{
		// Update the graphical mode activation timestamp with the current time on every left click.
		timeWhenGraphicalModeWasActivated = static_cast<float>(glfwGetTime());

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Cursor pos (x, y): (" << xpos << ", " << ypos << ")." << std::endl;
		// Do not continue processing mouse clicks if the orthogonal projection is turned off.
		if (!orthogonalProjectionTurnedOn)
		{
			return;
		}

		// door handle
		if (xpos >= 0.21125 * windowWidth && xpos <= 0.245 * windowWidth 
			&& ypos >= 0.425 * windowHeight && ypos <= 0.573333 * windowHeight)
		{
			if (doorState == DoorState::CLOSED)
			{
				doorState = DoorState::OPENING;
				// Scene should be lit if the refrigerator door is opened.
				sceneLit = true;
			}
			else if (doorState == DoorState::OPEN)
			{
				doorState = DoorState::CLOSING;
			}

			return;
		}

		// see-through mode activation button
		if (xpos >= 0.2225 * windowWidth && xpos <= 0.33 * windowWidth 
			&& ypos >= 0.236667 * windowHeight && ypos <= 0.286667 * windowHeight)
		{
			// Update see-through mode global variable.
			seeThroughModeTurnedOn = !seeThroughModeTurnedOn;
			// Scene should be lit if the see through mode is turned on.
			if (seeThroughModeTurnedOn)
			{
				sceneLit = true;
			}

			return;
		}

		// button for decreasing the intensity of the point light
		if (xpos >= 0.535 * windowWidth && xpos <= 0.57 * windowWidth 
			&& ypos >= 0.32 * windowHeight && ypos <= 0.346667 * windowHeight)
		{
			intensityOfBackgroundLight -= 0.02F;
			if (intensityOfBackgroundLight < 0.0F)
			{
				intensityOfBackgroundLight = 0.0F;
			}
			std::cout << "Intensity of background light : " << intensityOfBackgroundLight << std::endl;

			return;
		}
		// button for increasing the intensity of the point light
		if (xpos >= 0.73125 * windowWidth && xpos <= 0.7675 * windowWidth 
			&& ypos >= 0.32 * windowHeight && ypos <= 0.346667 * windowHeight)
		{
			intensityOfBackgroundLight += 0.02F;
			if (intensityOfBackgroundLight > 1.0F)
			{
				intensityOfBackgroundLight = 1.0F;
			}
			std::cout << "Intensity of background light : " << intensityOfBackgroundLight << std::endl;

			return;
		}

		float temperatureOffset = 0.1F;
		if (mods == GLFW_MOD_CONTROL)
		{
			temperatureOffset = 1.0F;
		}
		if (mods == GLFW_MOD_SHIFT)
		{
			temperatureOffset = 5.0F;
		}
		// "-" button, left of freezing chamber temperature widget
		if (xpos >= 0.535 * windowWidth && xpos <= 0.57 * windowWidth 
			&& ypos >= 0.141667 * windowHeight && ypos <= 0.19 * windowHeight)
		{
			currentTemperatureOfFreezingChamber -= temperatureOffset;
			if (currentTemperatureOfFreezingChamber < minTemperatureOfFreezingChamber)
			{
				currentTemperatureOfFreezingChamber = minTemperatureOfFreezingChamber;
			}

			return;
		}
		// "+" button, right of freezing chamber temperature widget
		if (xpos >= 0.73125 * windowWidth && xpos <= 0.7675 * windowWidth 
			&& ypos >= 0.141667 * windowHeight && ypos <= 0.19 * windowHeight)
		{
			currentTemperatureOfFreezingChamber += temperatureOffset;
			if (currentTemperatureOfFreezingChamber > maxTemperatureOfFreezingChamber)
			{
				currentTemperatureOfFreezingChamber = maxTemperatureOfFreezingChamber;
			}

			return;
		}
		// "-" button, left of refrigerating chamber temperature widget
		if (xpos >= 0.535 * windowWidth && xpos <= 0.57 * windowWidth 
			&& ypos >= 0.236667 * windowHeight && ypos <= 0.285 * windowHeight)
		{
			currentTemperatureOfRefrigeratingChamber -= temperatureOffset;
			if (currentTemperatureOfRefrigeratingChamber < minTemperatureOfRefrigeratingChamber)
			{
				currentTemperatureOfRefrigeratingChamber = minTemperatureOfRefrigeratingChamber;
			}

			return;
		}
		// "+" button, right of refrigerating chamber temperature widget
		if (xpos >= 0.73125 * windowWidth && xpos <= 0.7675 * windowWidth 
			&& ypos >= 0.236667 * windowHeight && ypos <= 0.285 * windowHeight)
		{
			currentTemperatureOfRefrigeratingChamber += temperatureOffset;
			if (currentTemperatureOfRefrigeratingChamber > maxTemperatureOfRefrigeratingChamber)
			{
				currentTemperatureOfRefrigeratingChamber = maxTemperatureOfRefrigeratingChamber;
			}

			return;
		}
	}
}
