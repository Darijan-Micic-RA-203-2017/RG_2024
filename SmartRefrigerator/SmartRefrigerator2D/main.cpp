#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

// Vertex shader, the first stage of the graphics pipeline. Shaders are written in the GLSL language.
const char *sourceCodeOfVertexShader = "#version 330 core\n\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec3 aColor;\n\n"
"out vec3 Color;\n\n"
"void main()\n"
"{"
"	Color = aColor;\n\n"
"	gl_Position = vec4(aPos, 0.0F, 1.0F);\n"
"}\n"
"\0";
// Fragment shader, the fifth stage of the graphics pipeline. Shaders are written in the GLSL language.
const char *sourceCodeOfFragmentShader = "#version 330 core\n\n"
"in vec3 Color;\n\n"
"out vec4 FragColor;\n\n"
"void main()\n"
"{"
"	FragColor = vec4(Color, 1.0F);\n"
"}\n"
"\0";

// The time difference (in seconds) between the end of renderings of the current frame and the previous frame.
// All velocities should be multiplied with the delta time value. The result is that when we have a large delta time,
// meaning that the rendering of the last frame took longer than average, the velocity for that frame will be a bit
// higher to balance it all out. When using this approach, it does not matter if the user has a very fast or slow PC,
// the velocity will be balanced out accordingly so each user will have the same experience. 
float deltaTime = 0.0F;
// The time (in seconds) it took to render the previous frame.
float previousFrameTime = 0.0F;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
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

	// Create the vertex shader object.
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach the source code of the vertex shader to its object.
	glShaderSource(vertexShader, 1, &sourceCodeOfVertexShader, NULL);
	// Dynamically compile the vertex shader at run-time.
	glCompileShader(vertexShader);
	// Check whether the compilation of vertex shader succeeded and print out the error if it did not.
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Vertex shader was not compiled!\n" << infoLog << std::endl;
		glfwTerminate();

		return 4;
	}

	// Create the fragment shader object.
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attach the source code of the fragment shader to its object.
	glShaderSource(fragmentShader, 1, &sourceCodeOfFragmentShader, NULL);
	// Dynamically compile the fragment shader at run-time.
	glCompileShader(fragmentShader);
	// Check whether the compilation of fragment shader succeeded and print out the error if it did not.
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (success == 0)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Fragment shader was not compiled!\n" << infoLog << std::endl;
		glfwTerminate();

		return 5;
	}

	// Create the shader program object.
	unsigned int shaderProgram = glCreateProgram();
	// Attach the previously compiled shaders to the shader program.
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link previously compiled shaders into a program.
	// The outputs of each shader are linked to the inputs of next shader.
	glLinkProgram(shaderProgram);
	// Check whether the linking of shader program succeeded and print out the error if it did not.
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Shader program was not linked!\n" << infoLog << std::endl;
		glfwTerminate();

		return 6;
	}
	// Delete shader objects after linking, they are no longer needed.
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	// Vertices in normalized device coordinates system (from -1.0F to 1.0F).
	float verticesofSquare[] = {
		// position     // color
		-0.75F, -0.75F, 0.0F, 0.0F, 1.0F, 
		 0.75F, -0.75F, 0.0F, 1.0F, 0.0F, 
		-0.75F,  0.75F, 1.0F, 0.0F, 0.0F, 
		 0.75F,  0.75F, 1.0F, 1.0F, 0.0F
	};

	// Create memory on the GPU where vertex data and index data will be stored.
	// Said data will be handled by VAO and vertex/element buffer objects inside that VAO.
	// Core OpenGL REQUIRES the use of VAOs!
	unsigned int squareVAO, squareVBO;
	glGenVertexArrays(1, &squareVAO);
	glGenBuffers(1, &squareVBO);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(squareVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, squareVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesofSquare), verticesofSquare, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Color attribute.
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (2 * sizeof(float)));
	// Enable vertex's color attribute.
	glEnableVertexAttribArray(1U);

	// Unbind VBO and VAO for safety reasons. This is not neccessary.
	// VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
	// This also means it stores its unbind calls, so
	// DO NOT EVER unbind EBO before unbinding VAO, otherwise it won't have a configured EBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0U);
	glBindVertexArray(0U);

	// Activate the desired shader program.
	glUseProgram(shaderProgram);

	// Rendering loop.
	while (glfwWindowShouldClose(window) == GLFW_FALSE)
	{
		// First part: calculate the new delta time and assign the current frame time to the previous frame time.
		float currentFrameTime = static_cast<float>(glfwGetTime());
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;

		// Second part: process the user's input.
		processInput(window);

		// Second part: rendering commands.
		glClearColor(0.1F, 0.1F, 0.1F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);

		// Bind (assign) the desired VAO to OpenGL's context.
		glBindVertexArray(squareVAO);
		// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
