#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "global_variables.hpp"
#include "texture.hpp"
#include "text.hpp"
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
	Texture fishSticksPackage("Resources/Images/Fish_sticks_package.png", false);
	if (fishSticksPackage.errorCode)
	{
		glfwTerminate();

		return fishSticksPackage.errorCode;
	}
	Texture milkCartonBox("Resources/Images/Milk_carton_box.png", false);
	if (milkCartonBox.errorCode)
	{
		glfwTerminate();

		return milkCartonBox.errorCode;
	}
	Texture blueSnowflakeIcon("Resources/Images/Blue_snowflake_icon.png", true);
	if (blueSnowflakeIcon.errorCode)
	{
		glfwTerminate();

		return blueSnowflakeIcon.errorCode;
	}

	// REFERENCE: https://www.glfw.org/docs/3.3/input_guide.html#cursor_custom
	GLFWimage imageOfBlueSnowflake;
	imageOfBlueSnowflake.width = blueSnowflakeIcon.width;
	imageOfBlueSnowflake.height = blueSnowflakeIcon.height;
	imageOfBlueSnowflake.pixels = blueSnowflakeIcon.pixels;
	blueSnowflakeCursor = glfwCreateCursor(&imageOfBlueSnowflake, 0, 0);
	if (blueSnowflakeCursor == NULL)
	{
		// De-allocate the texture used for the mouse cursor using the "stb_image.h" library's "stbi_image_free" method.
		stbi_image_free(blueSnowflakeIcon.pixels);
		glfwTerminate();

		return 9;
	}

	Font timesNewRomanFont("Resources/Fonts/times.ttf", textVAO, textVBO);
	if (timesNewRomanFont.errorCode != 0)
	{
		glfwTerminate();

		return timesNewRomanFont.errorCode;
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
			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForLogoText->useProgram();

			// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic
			// projection matrix will suffice. Using an orthographic projection matrix also allows all vertex
			// coordinates to be specified in screen-space coordinates. In order to take advantage of this, the
			// projection matrix needs to be set up this way:
			// glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
			// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen
			// (0.0F) to the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the
			// bottom-left corner.
			glm::mat4 projectionMatrix = 
				glm::ortho(0.0F, static_cast<float>(windowWidth), 0.0F, static_cast<float>(windowHeight));
			// Set the projection matrix. This matrix changes each frame.
			glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
			// Unbind UBO for safety reasons.
			glBindBuffer(GL_UNIFORM_BUFFER, 0U);

			// Set the current window width uniform.
			shaderProgramForLogoText->setFloatUniform("windowWidth", static_cast<float>(windowWidth));

			if (logoNeedsToPulse)
			{
				// Change the color of the "LOK" company's logo from blue to purple.
				redColorComponentForPulsing = glm::abs(glm::sin(currentFrameTime));
				// Update the red color component for pulsing uniform.
				shaderProgramForLogoText->setFloatUniform("redColorComponentForPulsing", redColorComponentForPulsing);
			}
			if (logoNeedsToMoveRight)
			{
				// Move the "LOK" company's logo to the right.
				bottomLeftXOfLogoText += 3.0F * glm::abs(sin(currentFrameTime));
				// Make the logo emerge on the opposite side of the screen space when the screen space's boundaries are
				// crossed.
				if (bottomLeftXOfLogoText > windowWidth)
				{
					bottomLeftXOfLogoText = -0.45F * windowWidth;
				}
			}
			if (logoNeedsToMoveInCircle)
			{
				// Move the "LOK" company's logo in a circle.
				float r = glm::min(windowWidth, windowHeight) / 5.0F;
				bottomLeftXOfLogoText = r * glm::cos(3.0F * currentFrameTime) + 0.225F * windowWidth;
				bottomLeftYOfLogoText = r * glm::sin(3.0F * currentFrameTime) + 0.4F * windowHeight;
			}
			if (logoNeedsToMoveLeftRightBetweenEdges)
			{
				// Move the "LOK" company's logo from left to right and vice-versa between the window's edges.
				// The closer the logo is to one of the edges, the more transparent it should be.
				float translationAmount = 3.0F * glm::abs(sin(currentFrameTime));
				if (logoNowNeedsToMoveTowardsLeftEdge)
				{
					bottomLeftXOfLogoText -= translationAmount;
					// Make the logo turn around when the screen space's boundaries are touched.
					if (bottomLeftXOfLogoText < 0.0F)
					{
						logoNowNeedsToMoveTowardsLeftEdge = !logoNowNeedsToMoveTowardsLeftEdge;
						bottomLeftXOfLogoText = 0.0F;
					}
				}
				else
				{
					bottomLeftXOfLogoText += translationAmount;
					// Make the logo turn around when the screen space's boundaries are touched.
					if (bottomLeftXOfLogoText > 0.5F * windowWidth)
					{
						logoNowNeedsToMoveTowardsLeftEdge = !logoNowNeedsToMoveTowardsLeftEdge;
						bottomLeftXOfLogoText = 0.5F * windowWidth;
					}
				}
			}

			// Render the "LOK" company's logo, scale it 4 times and paint it blue.
			timesNewRomanFont.renderText(*shaderProgramForLogoText, "LOK", 
				bottomLeftXOfLogoText, bottomLeftYOfLogoText, 4.0F, glm::vec3(0.0F, 0.0F, 1.0F));
		}
		else
		{
			// Set the active polygon mode (filled meshes mode, wireframe mode or point mode).
			glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForGrocery->useProgram();

			// Activate the texture unit (one of 16). After activating a texture unit, a subsequent "glBindTexture"
			// call will bind that texture to the currently active texture unit. The texture unit "GL_TEXTURE0" is
			// always active by default, so it isn't necessary to manually activate any texture unit if only one texture
			// is used.
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, fishSticksPackage.id);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, milkCartonBox.id);

			// The projection matrix transforms the view-space coordinates to the clip-space coordinates.
			// The projection that will be used is the perspective projection with the varying field of view (FOV) that
			// the user sets by scrolling, 0.1F near plane and 100.0F far plane. The ratio of the window's width and
			// height is called the aspect ratio.
			glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->fov), 
				static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1F, 100.0F);
			// Set the projection matrix. This matrix changes each frame.
			glBindBuffer(GL_UNIFORM_BUFFER, viewAndProjectionMatricesUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix[0U][0U]);
			// Unbind UBO for safety reasons.
			glBindBuffer(GL_UNIFORM_BUFFER, 0U);

			// The view matrix transforms the world-space coordinates to the view-space coordinates.
			// The world (scene) will be transformed by moving the camera using the keyboard.
			glm::mat4 viewMatrix = camera->getCalculatedViewMatrix();
			// Set the view matrix. This matrix changes each frame.
			glBindBuffer(GL_UNIFORM_BUFFER, viewAndProjectionMatricesUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix[0U][0U]);
			// Unbind UBO for safety reasons.
			glBindBuffer(GL_UNIFORM_BUFFER, 0U);

			// The model matrix transforms the local-space coordinates to the world-space coordinates.
			// The model matrix is simply an identity matrix, no transformation is applied.
			glm::mat4 modelMatrix = glm::mat4(1.0F);
			// Set the model matrix. This matrix changes each frame.
			shaderProgramForGrocery->setFloatMat4Uniform("modelMatrix", modelMatrix);

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(groceriesVAO);

			// Set the grocery inside freezer uniform.
			groceryInsideFreezer = !groceryInsideFreezer;
			shaderProgramForGrocery->setBoolUniform("groceryInsideFreezer", groceryInsideFreezer);

			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 36);  // left fish sticks package
			glDrawArrays(GL_TRIANGLES, 36, 36); // right fish sticks package

			// Set the grocery inside freezer uniform.
			groceryInsideFreezer = !groceryInsideFreezer;
			shaderProgramForGrocery->setBoolUniform("groceryInsideFreezer", groceryInsideFreezer);

			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 72, 36);  // left milk carton box
			glDrawArrays(GL_TRIANGLES, 108, 36); // right milk carton box

			// Depending on whether the see-through mode is turned on or off and whether the door is not closed or
			// is closed, render the chambers and the refrigerator door differently.
			if (seeThroughModeTurnedOn || doorState != DoorState::CLOSED)
			{
				glEnable(GL_BLEND);
			}
			else
			{
				glDisable(GL_BLEND);
			}

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForChamber->useProgram();

			// Set the model matrix. This matrix changes each frame.
			shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);

			// Set the current window width and height uniforms.
			shaderProgramForChamber->setFloatUniform("windowWidth", static_cast<float>(windowWidth));
			shaderProgramForChamber->setFloatUniform("windowHeight", static_cast<float>(windowHeight));
			// Set the current temperatures of each chamber uniforms.
			shaderProgramForChamber->setFloatUniform(
				"currentTemperatureOfFreezingChamber", currentTemperatureOfFreezingChamber);
			shaderProgramForChamber->setFloatUniform(
				"currentTemperatureOfRefrigeratingChamber", currentTemperatureOfRefrigeratingChamber);

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(chambersVAO);
			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 180);   // see-through, blue-tinted freezing chamber plastic
			glDrawArrays(GL_TRIANGLES, 180, 180); // see-through, blue-tinted refrigerating chamber plastic

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForRefrigerator->useProgram();

			// Set the model matrix. This matrix changes each frame.
			shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);
			// The normal matrix is a model matrix specifically tailored for normal vectors. Normal matrix is
			// defined as the transpose of the inverse of the upper-left 3x3 part of the model matrix.
			// Non-uniform scaling would transform vertex in such a way that the normal vector would no longer be
			// perpendicular to the vertex's surface. This means that the lighting of surface would be distorted.
			// Non-uniform scaling is mitigated by multiplying the normal vector with normal matrix.
			glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
			// Set the normal matrix. This matrix changes each frame.
			shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);

			float currentAvgTemperatureOfRefrigerator = 
				(currentTemperatureOfFreezingChamber + currentTemperatureOfRefrigeratingChamber) / 2.0F;
			// Set the is scene lit uniform.
			shaderProgramForRefrigerator->setBoolUniform("sceneLit", sceneLit);
			if (sceneLit)
			{
				// REFERENCE: https://learnopengl.com/Lighting/Light-casters
				// Set position of viewer to field "position" of global object "camera".
				shaderProgramForRefrigerator->setFloatVec3Uniform("positionOfViewer", camera->position);

				// Set the spotlight inside refrigerator uniforms.
				shaderProgramForRefrigerator->setFloatVec3Uniform(
					"lightSourceInsideRefrigerator.direction", glm::vec3(0.0F, 0.0F, 1.0F));
				shaderProgramForRefrigerator->setFloatVec3Uniform(
					"lightSourceInsideRefrigerator.position", glm::vec3(0.0F, 0.6F, -0.995F));
				shaderProgramForRefrigerator->setFloatUniform(
					"lightSourceInsideRefrigerator.cosOfInnerCutoffAngle", glm::cos(glm::radians(20.0F)));
				shaderProgramForRefrigerator->setFloatUniform(
					"lightSourceInsideRefrigerator.cosOfOuterCutoffAngle", glm::cos(glm::radians(30.0F)));
				float blueColorComponentOfLight = 
					(currentAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator) / 
					(maxAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator);
				shaderProgramForRefrigerator->setFloatVec3Uniform(
					"lightSourceInsideRefrigerator.ambientColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
				shaderProgramForRefrigerator->setFloatVec3Uniform(
					"lightSourceInsideRefrigerator.diffuseColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
				shaderProgramForRefrigerator->setFloatVec3Uniform(
					"lightSourceInsideRefrigerator.specularColor", glm::vec3(1.0F, 1.0F, 1.0F));
				// REFERENCE: https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
				// REFERENCE: https://wiki.ogre3d.org/Light%20Attenuation%20Shortcut
				// kC = 1.0F, kL = 4.5F / d, kQ = 75.0F / d^2; d = 5.0F
				shaderProgramForRefrigerator->setFloatUniform("lightSourceInsideRefrigerator.kC", 1.0F);
				shaderProgramForRefrigerator->setFloatUniform("lightSourceInsideRefrigerator.kL", 0.9F);
				shaderProgramForRefrigerator->setFloatUniform("lightSourceInsideRefrigerator.kQ", 3.0F);

				// Set the shininess of the specular highlight. Shininess value of highlight (the light source's beam)
				// determines the size (radius) and the scattering of specular highlight. This value should be a degree
				// of number 2 (2, 4, 8, 16, 32, ...).
				// Higher value results in a smaller, focused specular highlight. The light is reflected more properly.
				// Lower value results in a larger, scattered specular highlight. The light is reflected less properly.
				float shininessOfSpecularHighlight = 4.0F;
				shaderProgramForRefrigerator->setFloatUniform(
					"material.shininessOfSpecularHighlight", shininessOfSpecularHighlight);
			}

			// Set the current intensity of background light uniform.
			shaderProgramForRefrigerator->setFloatUniform("intensityOfBackgroundLight", intensityOfBackgroundLight);

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(refrigeratorVAO);
			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 36);      // refrigerator (back side)
			glDrawArrays(GL_TRIANGLES, 36, 36);     // refrigerator (left side)
			glDrawArrays(GL_TRIANGLES, 72, 36);     // refrigerator (right side)
			glDrawArrays(GL_TRIANGLES, 108, 36);    // refrigerator (bottom side)
			glDrawArrays(GL_TRIANGLES, 144, 36);    // refrigerator (top side)

			if (doorState == DoorState::OPENING)
			{
				// Set the model matrix. This matrix changes each frame.
				doorTranslation += 0.4F * deltaTime;
				if (doorTranslation > maxDoorTranslation)
				{
					doorTranslation = maxDoorTranslation;
				}
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, doorTranslation));
				doorAngle += 0.2F * deltaTime;
				if (doorAngle > maxDoorAngle)
				{
					doorAngle = maxDoorAngle;
					doorState = DoorState::OPEN;
				}
				modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
				shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

				// Set the normal matrix. This matrix changes each frame.
				normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
				shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
			}
			else if (doorState == DoorState::CLOSING)
			{
				// Set the model matrix. This matrix changes each frame.
				doorTranslation -= 0.4F * deltaTime;
				if (doorTranslation < minDoorTranslation)
				{
					doorTranslation = minDoorTranslation;
				}
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, doorTranslation));
				doorAngle -= 0.2F * deltaTime;
				if (doorAngle < minDoorAngle)
				{
					doorAngle = minDoorAngle;
					doorState = DoorState::CLOSED;
				}
				modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
				shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

				// Set the normal matrix. This matrix changes each frame.
				normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
				shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
			}
			else if (doorState == DoorState::OPEN)
			{
				// Set the model matrix. This matrix changes each frame.
				doorTranslation = maxDoorTranslation;
				modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, doorTranslation));
				doorAngle = maxDoorAngle;
				modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
				shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

				// Set the normal matrix. This matrix changes each frame.
				normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
				shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
			}
			else
			{
				// Set the model matrix. This matrix changes each frame.
				modelMatrix = glm::mat4(1.0F);
				shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

				// Set the normal matrix. This matrix changes each frame.
				normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
				shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
			}

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(refrigeratorDoorsVAO);
			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 36);    // refrigerator (front side)

			// Always turn on the blending when rendering the graphical elements and text, due to the way the "FreeType"
			// library is implemented.
			glEnable(GL_BLEND);

			glDrawArrays(GL_TRIANGLES, 36, 36);  // digital clock rectangle widget
			glDrawArrays(GL_TRIANGLES, 72, 36);  // see-through mode activation button
			glDrawArrays(GL_TRIANGLES, 108, 6);  // rectangle symbol on the see-through mode activation button
			glDrawArrays(GL_TRIANGLES, 114, 36); // doors handle, base
			glDrawArrays(GL_TRIANGLES, 150, 36); // doors handle, lower connector
			glDrawArrays(GL_TRIANGLES, 186, 36); // doors handle, upper connector
			glDrawArrays(GL_TRIANGLES, 222, 36); // doors handle, actual handle
			glDrawArrays(GL_TRIANGLES, 258, 36); // "-" button, left of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 294, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 296, 36); // freezing chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 332, 36); // "+" button, right of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 368, 4);      // lines representing the "+" sign itself
			glDrawArrays(GL_TRIANGLES, 372, 36); // "-" button, left of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 408, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 410, 36); // refrigerating chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 446, 36); // "+" button, right of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 482, 4);      // lines representing the "+" sign itself
			glDrawArrays(GL_TRIANGLES, 486, 36); // "-" button, left of point light intensity widget
			glDrawArrays(GL_LINES, 522, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 524, 36); // point light intensity widget
			glDrawArrays(GL_TRIANGLES, 560, 36); // "+" button, right of point light intensity widget
			glDrawArrays(GL_LINES, 596, 4);      // lines representing the "+" sign itself

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForLightSourceInsideRefrigerator->useProgram();

			// Set the model matrix. This matrix changes each frame.
			modelMatrix = glm::mat4(1.0F);
			shaderProgramForLightSourceInsideRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

			// Set the current temperatures of refrigerator uniform.
			shaderProgramForLightSourceInsideRefrigerator->setFloatUniform(
				"currentAvgTemperatureOfRefrigerator", currentAvgTemperatureOfRefrigerator);

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(lightSourceInsideRefrigeratorVAO);
			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 36);      // light source inside refrigerator (back side)
			glDrawArrays(GL_TRIANGLES, 36, 36);     // light source inside refrigerator (front side)
			glDrawArrays(GL_TRIANGLES, 72, 36);     // light source inside refrigerator (left side)
			glDrawArrays(GL_TRIANGLES, 108, 36);    // light source inside refrigerator (right side)
			glDrawArrays(GL_TRIANGLES, 144, 36);    // light source inside refrigerator (bottom side)
			glDrawArrays(GL_TRIANGLES, 180, 36);    // light source inside refrigerator (top side)

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForNonlogoText->useProgram();

			// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic
			// projection matrix will suffice. Using an orthographic projection matrix also allows all vertex coordinates to
			// be specified in screen-space coordinates. In order to take advantage of this, the projection matrix needs to
			// be set up this way: glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
			// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen
			// (0.0F) to the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the
			// bottom-left corner.
			projectionMatrix = glm::ortho(0.0F, static_cast<float>(windowWidth), 0.0F, static_cast<float>(windowHeight));
			// Set the projection matrix. This matrix changes each frame.
			glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
			// Unbind UBO for safety reasons.
			glBindBuffer(GL_UNIFORM_BUFFER, 0U);

			// REFERENCE: https://labex.io/tutorials/c-creating-a-simple-clock-animation-using-opengl-298829
			time_t rawTime;
			struct tm *timeInfo;
			time(&rawTime);
			timeInfo = localtime(&rawTime);
			int hours = timeInfo->tm_hour;
			int minutes = timeInfo->tm_min;
			int seconds = timeInfo->tm_sec;
			std::string hoursAsString = std::to_string(hours);
			if (hours < 10)
			{
				hoursAsString.insert(0, "0");
			}
			std::string minutesAsString = std::to_string(minutes);
			if (minutes < 10)
			{
				minutesAsString.insert(0, "0");
			}
			std::string secondsAsString = std::to_string(seconds);
			if (seconds < 10)
			{
				secondsAsString.insert(0, "0");
			}
			std::string currentTimeAsString = 
				hoursAsString.append(":").append(minutesAsString).append(":").append(secondsAsString);
			// Render the current time in the digital clock's space, scale it 2/3 times and paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, currentTimeAsString, 
				0.22625F * windowWidth, 0.81875F * windowHeight, 0.475F, glm::vec3(1.0F, 1.0F, 1.0F));

			std::string intensityOfBackgroundLightAsString = std::to_string(intensityOfBackgroundLight);
			intensityOfBackgroundLightAsString = intensityOfBackgroundLightAsString
				.substr(0U, intensityOfBackgroundLightAsString.size() - 4U);
			// Render the current intensity of the point light ("background light") in its widget's space, scale it
			// 2/3 times and paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, intensityOfBackgroundLightAsString, 
				0.6275F * windowWidth, 0.653333F * windowHeight, 0.475F, glm::vec3(1.0F, 1.0F, 1.0F));

			std::string currentTemperatureOfFreezingChamberAsString = 
				std::to_string(currentTemperatureOfFreezingChamber);
			currentTemperatureOfFreezingChamberAsString = currentTemperatureOfFreezingChamberAsString
				.substr(0U, currentTemperatureOfFreezingChamberAsString.size() - 5U);
			// Render the current temperature of the freezing chamber in its widget's space, scale it 2/3 times and
			// paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, currentTemperatureOfFreezingChamberAsString, 
				0.6125F * windowWidth, 0.816667F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

			std::string currentTemperatureOfRefrigeratingChamberAsString = 
				std::to_string(currentTemperatureOfRefrigeratingChamber);
			currentTemperatureOfRefrigeratingChamberAsString = currentTemperatureOfRefrigeratingChamberAsString
				.substr(0U, currentTemperatureOfRefrigeratingChamberAsString.size() - 5U);
			// Render the current temperature of the refrigerating chamber in its widget's space, scale it 2/3 times and
			// paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, currentTemperatureOfRefrigeratingChamberAsString, 
				0.63F * windowWidth, 0.718333F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

			// If 5 seconds have passed since the graphical mode was activated and no left click was registered, the
			// application should switch to the logo mode.
			// LOGO MODE IS TEMPORARILY DISABLED IN ORDER TO MAKE THE DEVELOPMENT EASIER (NO CLICKING REQUIRED)!!!
			/*
			if (currentFrameTime - timeWhenGraphicalModeWasActivated > 5.0F)
			{
				logoModeTurnedOn = true;
				graphicalModeTurnedOn = false;

				// Tell the GLFW library to release and show the mouse cursor, which is its normal mode.
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				// Reset the first mouse entry indicator to prevent the possible disappearance of the refrigerator from
				// the camera's view frustum.
				firstMouseEntry = true;

				// Activate the desired shader program.
				// Every shader and rendering call from now on will use this shader program object.
				shaderProgramForChamber->useProgram();

				// Update see-through mode global variable and uniform.
				seeThroughModeTurnedOn = false;
				shaderProgramForChamber->setBoolUniform("seeThroughModeTurnedOn", seeThroughModeTurnedOn);
			}
			*/
		}

		// Enable blending. FreeType library requires blending to be enabled in order to properly show glyphs.
		glEnable(GL_BLEND);

		// Activate the desired shader program.
		// Every shader and rendering call from now on will use this shader program object.
		shaderProgramForNonlogoText->useProgram();

		// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic
		// projection matrix will suffice. Using an orthographic projection matrix also allows all vertex
		// coordinates to be specified in screen-space coordinates. In order to take advantage of this, the
		// projection matrix needs to be set up this way:
		// glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
		// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen
		// (0.0F) to the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the
		// bottom-left corner.
		glm::mat4 projectionMatrix = 
			glm::ortho(0.0F, static_cast<float>(windowWidth), 0.0F, static_cast<float>(windowHeight));
		// Set the projection matrix. This matrix changes each frame.
		glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
		// Unbind UBO for safety reasons.
		glBindBuffer(GL_UNIFORM_BUFFER, 0U);

		// Set the current window width uniform.
		shaderProgramForNonlogoText->setFloatUniform("windowWidth", static_cast<float>(windowWidth));

		// Render the author's signature in the bottom left corner of the screen space, scale it 2/3 times and paint it
		// yellow.
		timesNewRomanFont.renderText(*shaderProgramForNonlogoText, "Darijan Micic, RA 203/2017", 
			glm::max(0.0125F * windowWidth, 10.0F), glm::max(0.016667F * windowHeight, 10.0F), 
			0.666667F, glm::vec3(1.0F, 1.0F, 0.0F));

		// Fourth part: swap buffers, check for events and call the events if they occured.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// In case the application's window gets launched again, reset the first mouse entry indicator.
	firstMouseEntry = true;

	// REFERENCE: https://www.geeksforgeeks.org/destructors-c/
	// De-allocate the camera using its destructor.
	delete camera;
	// De-allocate the texture used for the mouse cursor using the "stb_image.h" library's "stbi_image_free" method.
	stbi_image_free(blueSnowflakeIcon.pixels);
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
	if (!orthogonalProjectionTurnedOn || !(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS))
	{
		return;
	}

	if (logoModeTurnedOn)
	{
		logoModeTurnedOn = false;
		graphicalModeTurnedOn = true;
		seeThroughModeTurnedOn = false;
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
	// Do not allow moving the camera when the orthogonal projection is turned on.
	if (orthogonalProjectionTurnedOn)
	{
		// REFERENCE: https://www.glfw.org/docs/3.3/input_guide.html#cursor_set
		// If the mouse cursor is positioned above the freezing chamber, turn it to a blue snowflake.
		if (xpos >= 0.335 * windowWidth && xpos <= 0.66375 * windowWidth 
			&& ypos >= 0.396667 * windowHeight && ypos <= 0.605 * windowHeight)
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
