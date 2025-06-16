#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "global_variables.hpp"
#include "text.hpp"
#include "rendering.hpp"
#include "input_processing.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

int main()
{
	// Initialize the GLFW library.
	if (glfwInit() != GLFW_TRUE)
	{
		std::cout << "GLFW library was not initialized!" << std::endl;

		return 1;
	}
	// Specify the OpenGL version and profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window and make the context of created window the main context on the current thread.
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Smart refrigerator (3D)", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window was not created!" << std::endl;
		glfwTerminate();

		return 2;
	}
	glfwMakeContextCurrent(window);

	// Register the callback functions.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Initialize the GLEW library.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW library was not initialized!" << std::endl;
		glfwTerminate();

		return 3;
	}

	// Configure the global OpenGL state.

	// Enable the depth testing.
	glEnable(GL_DEPTH_TEST);
	// Enable the face culling.
	glEnable(GL_CULL_FACE);
	// Set the blending function. Its parameters:
	// 1) the source color factor - the factor of the output variable of the fragment shader;
	// 2) the destination color factor - the factor of the color of the fragment we are drawing over.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compile the shaders and link the shader programs using the helper "ShaderProgram" class.
	int errorCode = compileShadersAndLinkShaderPrograms();
	if (errorCode != 0)
	{
		// De-allocate the shader programs using their destructors.
		destroyShaderPrograms();
		glfwTerminate();

		return errorCode;
	}

	// Generate array and buffer objects, copy user-defined data to GPU and tell OpenGL how it should interpret it.
	// Finally, unbind array and buffer objects for safety reasons.
	setUpArrayAndBufferObjects();

	// Generate textures, set their wrapping and filtering parameters, load the images-to-become-textures from
	// the file system and generate all the required mipmaps using the helper class.
	errorCode = setUpTextures();
	if (errorCode != 0)
	{
		// De-allocate the textures using their destructors.
		destroyTextures();
		glfwTerminate();

		return errorCode;
	}

	// REFERENCE: https://www.glfw.org/docs/3.3/input_guide.html#cursor_custom
	GLFWimage imageOfBlueSnowflake;
	imageOfBlueSnowflake.width = blueSnowflakeIcon->width;
	imageOfBlueSnowflake.height = blueSnowflakeIcon->height;
	imageOfBlueSnowflake.pixels = blueSnowflakeIcon->pixels;
	blueSnowflakeCursor = glfwCreateCursor(&imageOfBlueSnowflake, 0, 0);
	if (blueSnowflakeCursor == NULL)
	{
		// De-allocate the texture used for the mouse cursor using the "stb_image.h" library's "stbi_image_free" method.
		stbi_image_free(blueSnowflakeIcon->pixels);
		glfwTerminate();

		return 9;
	}

	errorCode = setUpFonts();
	if (errorCode != 0)
	{
		// De-allocate the fonts using their destructors.
		destroyFonts();
		glfwTerminate();

		return errorCode;
	}

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForGrocery->useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForGrocery->setIntegerUniform("fishSticksPackage", 0);
	shaderProgramForGrocery->setIntegerUniform("milkCartonBox", 1);
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	unsigned int locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForGrocery->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForGrocery->id, locationOfUniformBlock, 0U);

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForChamber->useProgram();
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	locationOfUniformBlock = glGetUniformBlockIndex(shaderProgramForChamber->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForChamber->id, locationOfUniformBlock, 0U);

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForRefrigerator->useProgram();
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForRefrigerator->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForRefrigerator->id, locationOfUniformBlock, 0U);

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForLightSourceInsideRefrigerator->useProgram();
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForLightSourceInsideRefrigerator->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForLightSourceInsideRefrigerator->id, locationOfUniformBlock, 0U);

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForNonlogoText->useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForNonlogoText->setIntegerUniform("text", 0);
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ProjectionMatrix".
	locationOfUniformBlock = glGetUniformBlockIndex(shaderProgramForNonlogoText->id, "ProjectionMatrix");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForNonlogoText->id, locationOfUniformBlock, 1U);

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForLogoText->useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForLogoText->setIntegerUniform("text", 0);
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ProjectionMatrix".
	locationOfUniformBlock = glGetUniformBlockIndex(shaderProgramForLogoText->id, "ProjectionMatrix");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForLogoText->id, locationOfUniformBlock, 1U);

	// Create the camera with the default position, front vector and up vector using the helper "Camera" class.
	// The default position is glm::vec3(0.0F, 0.0F, 3.55F), the default front vector is glm::vec3(0.0F, 0.0F, -1.0F)
	// and the default up vector is glm::vec3(0.0F, 1.0F, 0.0F).
	camera = new Camera();

	glClearColor(0.1F, 0.1F, 0.1F, 1.0F);

	glfwSetTime(0.0);
	// Rendering loop.
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		// First part: calculate the new delta time and assign the current frame time to the previous frame time.
		currentFrameTime = static_cast<float>(glfwGetTime());
		deltaTime = currentFrameTime - previousFrameTime;
		frameRate = 1.0F / deltaTime;
		previousFrameTime = currentFrameTime;
		if (deltaTime < desiredMaxDeltaTime)
		{
			glfwWaitEventsTimeout(desiredMaxDeltaTime - deltaTime);
			currentFrameTime = static_cast<float>(glfwGetTime());
			deltaTime = currentFrameTime - previousFrameTime;
			previousFrameTime = currentFrameTime;
		}
		/*
		std::cout << "-------------------------" << std::endl;
		std::cout << "             Delta time: " << deltaTime << " s." << std::endl;
		std::cout << " Frame rate (1 / delta): " << frameRate << " s^(-1)." << std::endl;
		std::cout << "    Previous frame time: " << previousFrameTime << " s." << std::endl;
		*/

		// Second part: process the user's input.
		processInput(window);

		// Third part: rendering commands.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (logoModeTurnedOn)
		{
			renderLogoText();
		}
		else
		{
			// Set the active polygon mode (filled meshes mode, wireframe mode or point mode).
			glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

			renderGrocery();
			renderChamber();
			renderRefrigerator();
			renderRefrigeratorDoor();
			renderLightSourceInsideRefrigerator();
			renderNonlogoReadingsText();

			// If 5 seconds have passed since the graphical mode was activated and no left click was registered, the
			// application should switch to the logo mode.
			// LOGO MODE IS TEMPORARILY DISABLED IN ORDER TO MAKE THE DEVELOPMENT EASIER (NO CLICKING REQUIRED)!!!
			if (orthogonalProjectionTurnedOn && currentFrameTime - timeWhenGraphicalModeWasActivated > 5.0F)
			{
				logoModeTurnedOn = true;
				graphicalModeTurnedOn = false;

				// Tell the GLFW library to release and show the mouse cursor, which is its normal mode.
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				// Reset the first mouse entry indicator to prevent the possible disappearance of the refrigerator from
				// the camera's view frustum.
				firstMouseEntry = true;
			}
		}

		renderNonlogoSignatureText();

		// Fourth part: swap buffers, check for events and call the events if they occured.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// In case the application's window gets launched again, reset the first mouse entry indicator.
	firstMouseEntry = true;

	// REFERENCE: https://www.geeksforgeeks.org/destructors-c/
	// De-allocate the camera using its destructor.
	delete camera;
	// De-allocate the fonts using their destructors.
	destroyFonts();
	// De-allocate the texture used for the mouse cursor using the "stb_image.h" library's "stbi_image_free" method.
	stbi_image_free(blueSnowflakeIcon->pixels);
	// De-allocate the textures using their destructors.
	destroyTextures();
	// De-allocate the shader programs using their destructors.
	destroyShaderPrograms();

	// Terminate the GLFW library, which frees up all allocated resources.
	glfwTerminate();

	return 0;
}

// Callback functions.

// Function that will be called every time the application's window changes size.
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	glViewport(0, 0, width, height);
}

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
			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForChamber->useProgram();

			// Update see-through mode global variable and uniform.
			seeThroughModeTurnedOn = !seeThroughModeTurnedOn;
			shaderProgramForChamber->setBoolUniform("seeThroughModeTurnedOn", seeThroughModeTurnedOn);

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

// Function that will be called every time the user scrolls the mouse's middle button.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (orthogonalProjectionTurnedOn)
	{
		return;
	}

	camera->processMouseScroll(static_cast<float>(yoffset));
}
