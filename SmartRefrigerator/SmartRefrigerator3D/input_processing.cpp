#include "input_processing.hpp"

// Input processing function.
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		return;
	}

	if (graphicalModeTurnedOn)
	{
		// Move the camera (only when the perspective projection is turned on).
		if (!orthogonalProjectionTurnedOn)
		{
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				camera->processInputFromKeyboard("W", deltaTime);

				return;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				camera->processInputFromKeyboard("S", deltaTime);

				return;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				camera->processInputFromKeyboard("A", deltaTime);

				return;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				camera->processInputFromKeyboard("D", deltaTime);

				return;
			}
		}

		// Switch the polygon mode.
		if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		{
			polygonMode = GL_POINT;

			return;
		}
		if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		{
			polygonMode = GL_LINE;

			return;
		}
		if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		{
			polygonMode = GL_FILL;
			sceneLit = false;

			return;
		}
		if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			polygonMode = GL_FILL;
			sceneLit = true;

			return;
		}

		// Switch between the orthogonal projection (imitating the 2D project) and the perspective projection (used for
		// the 3D project).
		if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			// Update the graphical mode activation timestamp with the current time on every switch to the
			// orthogonal projection.
			timeWhenGraphicalModeWasActivated = static_cast<float>(glfwGetTime());

			orthogonalProjectionTurnedOn = true;
			// Tell the GLFW library to release and show the mouse cursor, which is its normal mode.
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Reset the camera so that it looks at the refrigerator's door.
			camera->resetToDefaultPositionMeantForOrthogonalProjection();

			return;
		}
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			orthogonalProjectionTurnedOn = false;
			// Tell the GLFW library to capture and hide the mouse cursor. Capturing the mouse cursor means fixating it
			// to the center of the application's window and only letting it move if the application loses focus or quits.
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			// Reset the mouse cursor to the default arrow one.
			glfwSetCursor(window, NULL);
			// Reset the first mouse entry indicator to prevent the possible disappearance of the refrigerator from
			// the camera's view frustum.
			firstMouseEntry = true;

			return;
		}

		return;
	}

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForLogoText->useProgram();

	// Reset everything related to the logo.
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		// Reset the logo needs to pulse global variable and uniform and its associates.
		logoNeedsToPulse = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToPulse", logoNeedsToPulse);
		redColorComponentForPulsing = 0.0F;
		shaderProgramForLogoText->setFloatUniform("redColorComponentForPulsing", redColorComponentForPulsing);
		// Reset the logo needs to move right global variable and its associates.
		logoNeedsToMoveRight = false;
		// Reset the logo needs to move in circle global variable and its associates.
		logoNeedsToMoveInCircle = false;
		// Reset the logo needs to move left-right between edges global variable and uniform and its associates.
		logoNeedsToMoveLeftRightBetweenEdges = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;
		bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
		bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);

		return;
	}
	// Pulse the color of the "LOK" company's logo. In other words, change it from blue to purple over time.
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		// Reset the logo needs to move right global variable and its associates.
		logoNeedsToMoveRight = false;
		// Reset the logo needs to move in circle global variable and its associates.
		logoNeedsToMoveInCircle = false;
		// Reset the logo needs to move left-right between edges global variable and uniform and its associates.
		logoNeedsToMoveLeftRightBetweenEdges = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;
		bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
		bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);

		// Update the logo needs to pulse global variable and uniform.
		logoNeedsToPulse = true;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToPulse", logoNeedsToPulse);

		return;
	}
	// Move the "LOK" company's logo to the right. Once it reaches the right edge of the window, it appears on the
	// left edge of the window.
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		// Reset the logo needs to pulse global variable and uniform and its associates.
		logoNeedsToPulse = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToPulse", logoNeedsToPulse);
		redColorComponentForPulsing = 0.0F;
		shaderProgramForLogoText->setFloatUniform("redColorComponentForPulsing", redColorComponentForPulsing);
		// Reset the logo needs to move in circle global variable and its associates.
		logoNeedsToMoveInCircle = false;
		// Reset the logo needs to move left-right between edges global variable and uniform and its associates.
		logoNeedsToMoveLeftRightBetweenEdges = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;
		bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
		bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);

		// Update the logo needs to move right global variable.
		logoNeedsToMoveRight = true;

		return;
	}
	// Move the "LOK" company's logo in a circle.
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		// Reset the logo needs to pulse global variable and uniform and its associates.
		logoNeedsToPulse = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToPulse", logoNeedsToPulse);
		redColorComponentForPulsing = 0.0F;
		shaderProgramForLogoText->setFloatUniform("redColorComponentForPulsing", redColorComponentForPulsing);
		// Reset the logo needs to move right global variable and its associates.
		logoNeedsToMoveRight = false;
		// Reset the logo needs to move left-right between edges global variable and uniform and its associates.
		logoNeedsToMoveLeftRightBetweenEdges = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;
		bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
		bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);

		// Update the logo needs to move in circle global variable.
		logoNeedsToMoveInCircle = true;

		return;
	}
	// Move the "LOK" company's logo from left to right and vice-versa between the window's edges. The closer the logo
	// is to one of the edges, the more transparent it should be.
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		// Reset the logo needs to pulse global variable and uniform and its associates.
		logoNeedsToPulse = false;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToPulse", logoNeedsToPulse);
		redColorComponentForPulsing = 0.0F;
		shaderProgramForLogoText->setFloatUniform("redColorComponentForPulsing", redColorComponentForPulsing);
		// Reset the logo needs to move right global variable and its associates.
		logoNeedsToMoveRight = false;
		// Reset the logo needs to move in circle global variable and its associates.
		logoNeedsToMoveInCircle = false;
		bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
		bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);

		// Update the logo needs to move left-right between edges global variable and uniform and its associate.
		logoNeedsToMoveLeftRightBetweenEdges = true;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;
	}
}
