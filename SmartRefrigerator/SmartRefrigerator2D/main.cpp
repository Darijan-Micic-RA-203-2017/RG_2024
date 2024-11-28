#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include "shader_program.hpp"
#include "texture.hpp"

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
	ShaderProgram shaderProgram0("vertex_shader.glsl", "fragment_shader.glsl");
	if (shaderProgram0.errorCode != 0)
	{
		glfwTerminate();

		return shaderProgram0.errorCode;
	}
	ShaderProgram shaderProgram1("vertex_shader_of_square.glsl", "fragment_shader_of_square.glsl");
	if (shaderProgram1.errorCode != 0)
	{
		glfwTerminate();

		return shaderProgram1.errorCode;
	}

	// Vertices in the normalized device coordinates system (from -1.0F to 1.0F).
	float verticesOfAuthorSignature[] = {
		// position      // color                // texture coordinates
		0.100F, -0.975F, 0.1F, 0.1F, 0.1F, 1.0F, 0.0F, 0.0F, 
		0.975F, -0.975F, 0.1F, 0.1F, 0.1F, 1.0F, 0.0F, 1.0F, 
		0.100F, -0.825F, 0.1F, 0.1F, 0.1F, 1.0F, 1.0F, 0.0F, 
		0.975F, -0.825F, 0.1F, 0.1F, 0.1F, 1.0F, 1.0F, 1.0F
	};
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
	unsigned int authorSignatureVAO, refrigeratorVAO, authorSignatureVBO, refrigeratorVBO;
	glGenVertexArrays(1, &authorSignatureVAO);
	glGenVertexArrays(1, &refrigeratorVAO);
	glGenBuffers(1, &authorSignatureVBO);
	glGenBuffers(1, &refrigeratorVBO);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(authorSignatureVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, authorSignatureVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfAuthorSignature), verticesOfAuthorSignature, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Color attribute.
	glVertexAttribPointer(1U, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (2 * sizeof(float)));
	// Enable vertex's color attribute.
	glEnableVertexAttribArray(1U);
	// Texture coordinates attribute.
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
	// Enable vertex's texture coordinates attribute.
	glEnableVertexAttribArray(2U);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(refrigeratorVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, refrigeratorVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfRefrigerator), verticesOfRefrigerator, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Color attribute.
	glVertexAttribPointer(1U, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (2 * sizeof(float)));
	// Enable vertex's color attribute.
	glEnableVertexAttribArray(1U);

	// Unbind VBO and VAO for safety reasons. This is not neccessary.
	// VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
	// This also means it stores its unbind calls, so
	// DO NOT EVER unbind EBO before unbinding VAO, otherwise it won't have a configured EBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0U);
	glBindVertexArray(0U);

	Texture authorSignatureTexture("Resources/RG_providno_ime_prezime_brojIndeksa_1280x128.png");
	if (authorSignatureTexture.errorCode)
	{
		glfwTerminate();

		return authorSignatureTexture.errorCode;
	}

	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgram0.useProgram();
	shaderProgram0.setIntegerUniform("texture0", 0);

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
		shaderProgram0.useProgram();

		// Activate a texture unit (one of 16). After activating a texture unit, a subsequent "glBindTexture" call will
		// bind that texture to the currently active texture unit. The texture unit "GL_TEXTURE0" is always active by
		// default, so it is not necessary to manually activate any texture unit if only one texture is used.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, authorSignatureTexture.id);

		// Bind (assign) the desired VAO to OpenGL's context.
		glBindVertexArray(authorSignatureVAO);
		// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		// Activate the desired shader program.
		// Every shader and rendering call from now on will use this shader program object.
		shaderProgram1.useProgram();

		// Bind (assign) the desired VAO to OpenGL's context.
		glBindVertexArray(refrigeratorVAO);
		// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
