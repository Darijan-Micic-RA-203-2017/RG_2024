#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_programs.hpp"
#include "vaos_and_vbos.hpp"
#include "texture.hpp"
#include "text.hpp"
#include "camera.hpp"

int windowWidth = 800;
int windowHeight = 600;

// All settings are kept in an instance of the camera class.
Camera *camera = NULL;
// The cursor that will be shown when the mouse is hovering over the freezing chamber in the orthogonal projection mode.
GLFWcursor *blueSnowflakeCursor = NULL;
// Is this the first time the mouse entry is captured?
bool firstMouseEntry = true;
// Previous cursor position is initialized to the half of the window's size.
float previousCursorPosX = static_cast<float>(windowWidth) / 2.0F;
float previousCursorPosY = static_cast<float>(windowHeight) / 2.0F;

// The current time (in seconds) after the initialization of the GLFW library.
float currentFrameTime = 0.0F;
// The time difference (in seconds) between the end of renderings of the current frame and the previous frame.
// All velocities should be multiplied with the delta time value. The result is that when we have a large delta time,
// meaning that the rendering of the last frame took longer than average, the velocity for that frame will be a bit
// higher to balance it all out. When using this approach, it does not matter if the user has a very fast or slow PC,
// the velocity will be balanced out accordingly so each user will have the same experience. 
float deltaTime = 0.0F;
float frameRate = 0.0F;
const float desiredMaxDeltaTime = 0.016667F; // 1 / 60
// The time (in seconds) it took to render the previous frame.
float previousFrameTime = 0.0F;

// The logo mode starts 5 seconds after the user last clicked on the refrigerator's graphic display and ends when the
// user clicks on it again. Logo mode consists of showing the "LOK" company logo over the screen.
bool logoModeTurnedOn = false;
// Pressing the "2" key should start the color pulsing of the "LOK" company's logo.
bool logoNeedsToPulse = false;
float redColorComponentForPulsing = 0.0F;
// Pressing the "3" key should start the movement of the "LOK" company's logo to the right. Once it reaches the right
// edge of the window, it should appear on the left edge of the window.
bool logoNeedsToMoveRight = false;
// Pressing the "4" key should start the movement of the "LOK" company's logo in a circle.
bool logoNeedsToMoveInCircle = false;
// Pressing the "5" key should start the movement of the "LOK" company's logo from left to right and vice-versa between
// the window's edges. The closer the logo is to one of the edges, the more transparent it should be.
bool logoNeedsToMoveLeftRightBetweenEdges = false;
bool logoNowNeedsToMoveTowardsLeftEdge = true;
float bottomLeftXOfLogoText = 0.275F * windowWidth;
float bottomLeftYOfLogoText = 0.4F * windowHeight;

// The graphical mode is the initial mode of the application. It also starts after the user clicks anywhere on the
// screen during the logo mode. Graphic mode consists of showing the temperature widgets for the freezing and the
// refrigerating chamber and the digital clock.
bool graphicalModeTurnedOn = true;
float timeWhenGraphicalModeWasActivated = 0.0F;
GLenum polygonMode = GL_FILL;
bool sceneLit = true;
// When the orthogonal projection is turned on, this 3D project acts as the 2D project and the mouse cursor is visible.
// Otherwise, the entire refrigerator can be seen and the mouse cursor is hidden.
bool orthogonalProjectionTurnedOn = true;
bool groceryInsideFreezer = false;
const float minTemperatureOfFreezingChamber = -40.0F;
float currentTemperatureOfFreezingChamber = -29.0F;
const float maxTemperatureOfFreezingChamber = -18.0F;
const float minTemperatureOfRefrigeratingChamber = 0.0F;
float currentTemperatureOfRefrigeratingChamber = 3.5F;
const float maxTemperatureOfRefrigeratingChamber = 7.0F;
const float minAvgTemperatureOfRefrigerator = -20.0F;
const float maxAvgTemperatureOfRefrigerator = -5.5F;
// This factor affects not only the intensity of background, but all elements of graphic display.
float intensityOfBackgroundLight = 1.0F;

// The see-through mode starts after the user clicks on that mode activation button during the graphical mode.
// See-through mode consists of showing the groceries inside the smart refrigerator.
float seeThroughModeTurnedOn = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

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

	// Generate vertex arrays and buffers, copy user-defined data to GPU and tell OpenGL how it should interpret it.
	// Finally, unbind VBO and VAO for safety reasons.
	setUpVAOsAndVBOs();

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

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForNonlogoText->useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForNonlogoText->setIntegerUniform("text", 0);
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForLogoText->useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForLogoText->setIntegerUniform("text", 0);

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
			shaderProgramForLogoText->setFloatMat4Uniform("projectionMatrix", projectionMatrix);

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
			shaderProgramForGrocery->setFloatMat4Uniform("projectionMatrix", projectionMatrix);

			// The view matrix transforms the world-space coordinates to the view-space coordinates.
			// The world (scene) will be transformed by moving the camera using the keyboard.
			glm::mat4 viewMatrix = camera->getCalculatedViewMatrix();
			// Set the view matrix. This matrix changes each frame.
			shaderProgramForGrocery->setFloatMat4Uniform("viewMatrix", viewMatrix);

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

			// Depending on whether the see-through mode is turned on or off, render the chambers and the refrigerator
			// doors differently.
			if (seeThroughModeTurnedOn)
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

			// Set the projection matrix. This matrix changes each frame.
			shaderProgramForChamber->setFloatMat4Uniform("projectionMatrix", projectionMatrix);
			// Set the view matrix. This matrix changes each frame.
			shaderProgramForChamber->setFloatMat4Uniform("viewMatrix", viewMatrix);
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
			glDrawArrays(GL_TRIANGLES, 0, 30);  // see-through, blue-tinted freezing chamber plastic
			glDrawArrays(GL_TRIANGLES, 30, 30); // see-through, blue-tinted refrigerating chamber plastic

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForRefrigerator->useProgram();

			// Set the projection matrix. This matrix changes each frame.
			shaderProgramForRefrigerator->setFloatMat4Uniform("projectionMatrix", projectionMatrix);
			// Set the view matrix. This matrix changes each frame.
			shaderProgramForRefrigerator->setFloatMat4Uniform("viewMatrix", viewMatrix);
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
			glDrawArrays(GL_TRIANGLES, 114, 36); // "-" button, left of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 150, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 152, 36); // freezing chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 188, 36); // "+" button, right of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 224, 4);      // lines representing the "+" sign itself
			glDrawArrays(GL_TRIANGLES, 228, 36); // "-" button, left of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 264, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 266, 36); // refrigerating chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 302, 36); // "+" button, right of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 338, 4);      // lines representing the "+" sign itself
			glDrawArrays(GL_TRIANGLES, 342, 36); // "-" button, left of point light intensity widget
			glDrawArrays(GL_LINES, 378, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 380, 36); // point light intensity widget
			glDrawArrays(GL_TRIANGLES, 416, 36); // "+" button, right of point light intensity widget
			glDrawArrays(GL_LINES, 452, 4);      // lines representing the "+" sign itself

			// Activate the desired shader program.
			// Every shader and rendering call from now on will use this shader program object.
			shaderProgramForLightSourceInsideRefrigerator->useProgram();

			// Set the projection matrix. This matrix changes each frame.
			shaderProgramForLightSourceInsideRefrigerator->setFloatMat4Uniform("projectionMatrix", projectionMatrix);
			// Set the view matrix. This matrix changes each frame.
			shaderProgramForLightSourceInsideRefrigerator->setFloatMat4Uniform("viewMatrix", viewMatrix);
			// Set the model matrix. This matrix changes each frame.
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
			shaderProgramForNonlogoText->setFloatMat4Uniform("projectionMatrix", projectionMatrix);

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
		shaderProgramForNonlogoText->setFloatMat4Uniform("projectionMatrix", projectionMatrix);

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

// Funtion that processes clicking on mouse buttons.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
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

// Input processing function.
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);

		return;
	}

	if (!logoModeTurnedOn)
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
		bottomLeftXOfLogoText = 0.275F * windowWidth;
		bottomLeftYOfLogoText = 0.4F * windowHeight;

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
		bottomLeftXOfLogoText = 0.275F * windowWidth;
		bottomLeftYOfLogoText = 0.4F * windowHeight;

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
		bottomLeftXOfLogoText = 0.275F * windowWidth;
		bottomLeftYOfLogoText = 0.4F * windowHeight;

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
		bottomLeftXOfLogoText = 0.275F * windowWidth;
		bottomLeftYOfLogoText = 0.4F * windowHeight;

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
		bottomLeftXOfLogoText = 0.275F * windowWidth;
		bottomLeftYOfLogoText = 0.4F * windowHeight;

		// Update the logo needs to move left-right between edges global variable and uniform and its associate.
		logoNeedsToMoveLeftRightBetweenEdges = true;
		shaderProgramForLogoText->setBoolUniform("logoNeedsToMoveLeftRightBetweenEdges", logoNeedsToMoveLeftRightBetweenEdges);
		logoNowNeedsToMoveTowardsLeftEdge = true;

		return;
	}
}
