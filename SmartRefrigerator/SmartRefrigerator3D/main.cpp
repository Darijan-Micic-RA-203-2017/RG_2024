#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "global_variables.hpp"
#include "text.hpp"
#include "rendering.hpp"
#include "callbacks.hpp"

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
	/*
	// Retrieve the location index of the uniform block named "RequiredLightingData".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForGrocery->id, "RequiredLightingData");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForGrocery->id, locationOfUniformBlock, 2U);
	*/

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForChamber->useProgram();
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	locationOfUniformBlock = glGetUniformBlockIndex(shaderProgramForChamber->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForChamber->id, locationOfUniformBlock, 0U);
	/*
	// Retrieve the location index of the uniform block named "RequiredLightingData".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForChamber->id, "RequiredLightingData");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForChamber->id, locationOfUniformBlock, 2U);
	*/

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForRefrigerator->useProgram();
	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
	// Retrieve the location index of the uniform block named "ViewAndProjectionMatrices".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForRefrigerator->id, "ViewAndProjectionMatrices");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForRefrigerator->id, locationOfUniformBlock, 0U);
	/*
	// Retrieve the location index of the uniform block named "RequiredLightingData".
	locationOfUniformBlock = 
		glGetUniformBlockIndex(shaderProgramForRefrigerator->id, "RequiredLightingData");
	// Tell OpenGL to what binding point each uniform block is set to.
	glUniformBlockBinding(shaderProgramForRefrigerator->id, locationOfUniformBlock, 2U);
	*/

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

	unsigned int frameCounter = 0U;

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
		// Print time data of every 5th frame.
		frameCounter++;
		if (frameCounter % 5U == 0U)
		{
			frameCounter = 0U;
			std::cout << "-------------------------" << std::endl;
			std::cout << "             Delta time: " << deltaTime << " s." << std::endl;
			std::cout << " Frame rate (1 / delta): " << frameRate << " s^(-1)." << std::endl;
			std::cout << "    Previous frame time: " << previousFrameTime << " s." << std::endl;
		}

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
			// Render the nonlogo readings text only if the orthogonal projection is turned on and
			// the refrigerator door is closed.
			if (orthogonalProjectionTurnedOn && doorState == DoorState::CLOSED)
			{
				renderNonlogoReadingsText();
			}

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
