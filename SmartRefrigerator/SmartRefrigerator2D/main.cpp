#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include "shader_program.hpp"
#include "texture.hpp"
#include "text.hpp"

int windowWidth = 800;
int windowHeight = 600;

// The time difference (in seconds) between the end of renderings of the current frame and the previous frame.
// All velocities should be multiplied with the delta time value. The result is that when we have a large delta time,
// meaning that the rendering of the last frame took longer than average, the velocity for that frame will be a bit
// higher to balance it all out. When using this approach, it does not matter if the user has a very fast or slow PC,
// the velocity will be balanced out accordingly so each user will have the same experience. 
float deltaTime = 0.0F;
// float frameRate = 0.0F;
// The number of frames rendered in one second, a reciprocal value of delta time (1.0F / delta time).
double frameRate = 0.0;
// It is requested to limit the speed of rendering to 60 frames per second.
const double desiredFrameRate = 60.0;
// The time (in seconds) it took to render the previous frame.
float previousFrameTime = 0.0F;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// REFERENCE: https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter?noredirect=1&lq=1
double clockFrequencyOfPC = 0.0;
__int64 startingValueOfCounter = 0;
double previousValueOfCounter = 0.0;

void startCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
	{
		std::cout << "QueryPerformanceFrequency failed!" << std::endl;

		return;
	}

	clockFrequencyOfPC = double(li.QuadPart);

	QueryPerformanceCounter(&li);
	startingValueOfCounter = li.QuadPart;
}

double getValueOfCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);

	return double(li.QuadPart - startingValueOfCounter) / clockFrequencyOfPC;
}

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
	GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "Smart refrigerator (2D)", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Window was not created!" << std::endl;
		glfwTerminate();

		return 2;
	}
	glfwMakeContextCurrent(window);

	// Register the callback functions.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Initialize the GLEW library.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW library was not initialized!" << std::endl;
		glfwTerminate();

		return 3;
	}

	// Configure the global OpenGL state.
	// Enable blending.
	glEnable(GL_BLEND);
	// Set the blending function. Its parameters:
	// 1) the source color factor - the factor of the output variable of the fragment shader;
	// 2) the destination color factor - the factor of the color of the fragment we are drawing over.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compile the shaders and link the shader programs using the helper "ShaderProgram" class.
	ShaderProgram shaderProgramForRefrigerator("vertex_shader_of_refrigerator.glsl", "fragment_shader_of_refrigerator.glsl");
	if (shaderProgramForRefrigerator.errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForRefrigerator.errorCode;
	}
	ShaderProgram shaderProgramForText("vertex_shader_of_text.glsl", "fragment_shader_of_text.glsl");
	if (shaderProgramForText.errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForText.errorCode;
	}

	// Vertices in the normalized device coordinates system (from -1.0F to 1.0F).
	float verticesOfRefrigerator[] = {
		// position   // color
		-0.8F, -0.8F, 0.0F, 0.0F, 1.0F, 1.0F, 
		 0.8F, -0.8F, 0.0F, 1.0F, 0.0F, 1.0F, 
		-0.8F,  0.8F, 1.0F, 0.0F, 0.0F, 1.0F, 
		 0.8F,  0.8F, 1.0F, 1.0F, 0.0F, 1.0F
	};

	// Create memory on the GPU where vertex data and index data will be stored.
	// Said data will be handled by VAO and vertex/element buffer objects inside that VAO.
	// Core OpenGL REQUIRES the use of VAOs!
	unsigned int refrigeratorVAO, textVAO, refrigeratorVBO, textVBO;
	glGenVertexArrays(1, &refrigeratorVAO);
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &refrigeratorVBO);
	glGenBuffers(1, &textVBO);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(refrigeratorVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, refrigeratorVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfRefrigerator), verticesOfRefrigerator, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 6U * sizeof(float), (void*) 0U);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Color attribute.
	glVertexAttribPointer(1U, 4, GL_FLOAT, GL_FALSE, 6U * sizeof(float), (void*) (2U * sizeof(float)));
	// Enable vertex's color attribute.
	glEnableVertexAttribArray(1U);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(textVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, 6U * 4U * sizeof(float), NULL, GL_DYNAMIC_DRAW); // For often updates of the content.
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position and texture coordinates (combined) attribute.
	glVertexAttribPointer(0U, 4, GL_FLOAT, GL_FALSE, 4U * sizeof(float), (void*) 0U);
	// Enable vertex's position and texture coordinates (combined) attribute.
	glEnableVertexAttribArray(0U);

	// Unbind VBO and VAO for safety reasons. This is not neccessary.
	// VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
	// This also means it stores its unbind calls, so
	// DO NOT EVER unbind EBO before unbinding VAO, otherwise it won't have a configured EBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0U);
	glBindVertexArray(0U);

	Text authorSignatureText("Resources/Fonts/times.ttf", textVAO, textVBO);
	if (authorSignatureText.errorCode != 0)
	{
		glfwTerminate();

		return authorSignatureText.errorCode;
	}

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForRefrigerator.useProgram();
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForText.useProgram();
	// Tell OpenGL to which texture unit each shader sampler belongs to, by setting each sampler.
	shaderProgramForText.setIntegerUniform("text", 0);

	// Retrieve the location of the uniform variable "projectionMatrix" in the shader program for text.
	// This doesn't require the activation of the shader program.
	int locationOfProjectionMatrix = glGetUniformLocation(shaderProgramForText.id, "projectionMatrix");
	// If the uniform variable's location wasn't found, the "glGetUniformLocation" function returns -1.
	if (locationOfProjectionMatrix == -1)
	{
		std::cout << "Location of uniform variable \"projectionMatrix\" wasn't found!" << std::endl;
		glfwTerminate();

		return 11;
	}

	glClearColor(0.1F, 0.1F, 0.1F, 1.0F);

	glfwSetTime(0.0);
	// REFERENCE: https://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter?noredirect=1&lq=1
	startCounter();

	// Rendering loop.
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		// First part: calculate the new delta time and assign the current frame time to the previous frame time.
		float currentFrameTime = static_cast<float>(glfwGetTime());
		deltaTime = currentFrameTime - previousFrameTime;
		// frameRate = 1.0F / deltaTime;
		previousFrameTime = currentFrameTime;
		std::cout << "-------------------------" << std::endl;
		// std::cout << "             Delta time: " << deltaTime << " s." << std::endl;
		// std::cout << " Frame rate (1 / delta): " << frameRate << " s^(-1)." << std::endl;
		// std::cout << "    Previous frame time: " << previousFrameTime << " s." << std::endl;
		/*
		if (frameRate > 60.0f)
		{
			Sleep(500);
		}
		*/

		// Second part: process the user's input.
		processInput(window);

		// Third part: rendering commands.
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate the desired shader program.
		// Every shader and rendering call from now on will use this shader program object.
		shaderProgramForRefrigerator.useProgram();

		// Bind (assign) the desired VAO to OpenGL's context.
		glBindVertexArray(refrigeratorVAO);
		// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Activate the desired shader program.
		// Every shader and rendering call from now on will use this shader program object.
		shaderProgramForText.useProgram();

		// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic
		// projection matrix will suffice. Using an orthographic projection matrix also allows all vertex coordinates to
		// be specified in screen-space coordinates. In order to take advantage of this, the projection matrix needs to
		// be set up this way: glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
		// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen
		// (0.0F) to the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the
		// bottom-left corner.
		glm::mat4 projectionMatrix = 
			glm::ortho(0.0F, static_cast<float>(windowWidth), 0.0F, static_cast<float>(windowHeight));
		// Set the projection matrix. This matrix changes each frame.
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramForText.id, "projectionMatrix"), 
			1, GL_FALSE, &projectionMatrix[0U][0U]);

		// Render author's signature in the bottom left corner of the screen space.
		authorSignatureText.renderText(shaderProgramForText, "Darijan Micic, RA 203/2017", 
			5.0F, 5.0F, 1.0F, glm::vec3(1.0F, 1.0F, 0.0F));

		double time = getValueOfCounter();
		std::cout << "Counter (s): " << time << "\n";
		frameRate = 1.0 / (time - previousValueOfCounter);
		std::cout << "Frame rate (1 / counter): " << frameRate << " s^(-1)." << std::endl;
		if (frameRate > desiredFrameRate + 10.0)
		{
			Sleep(350);
		}
		else if (frameRate > desiredFrameRate)
		{
			Sleep(150);
		}
		previousValueOfCounter = time;

		// Fourth part: swap buffers, check for events and call the events if they occured.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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

// Input processing function.
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
