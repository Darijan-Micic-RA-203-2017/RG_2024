#define _CRT_SECURE_NO_WARNINGS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader_program.hpp"
#include "texture.hpp"
#include "text.hpp"
#include "camera.hpp"

int windowWidth = 800;
int windowHeight = 600;

// All settings are kept in an instance of the camera class.
Camera *camera = NULL;

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

// Shader programs.
ShaderProgram *shaderProgramForGrocery = NULL;
ShaderProgram *shaderProgramForChamber = NULL;
ShaderProgram *shaderProgramForRefrigerator = NULL;
ShaderProgram *shaderProgramForNonlogoText = NULL;
ShaderProgram *shaderProgramForLogoText = NULL;

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
bool groceryInsideFreezer = false;
const float minTemperatureOfFreezingChamber = -40.0F;
float currentTemperatureOfFreezingChamber = -29.0F;
const float maxTemperatureOfFreezingChamber = -18.0F;
const float minTemperatureOfRefrigeratingChamber = 0.0F;
float currentTemperatureOfRefrigeratingChamber = 3.5F;
const float maxTemperatureOfRefrigeratingChamber = 7.0F;

// The see-through mode starts after the user clicks on that mode activation button during the graphical mode.
// See-through mode consists of showing the groceries inside the smart refrigerator.
float seeThroughModeTurnedOn = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);
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

	// Tell the GLFW library to capture and hide the mouse cursor. Capturing the mouse cursor means fixating it to the
	// center of the application's window and only letting it move if the application loses focus or quits.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	shaderProgramForGrocery = new ShaderProgram("Shaders/Grocery/vertex_shader_of_grocery.glsl", 
		"Shaders/Grocery/fragment_shader_of_grocery.glsl");
	if (shaderProgramForGrocery->errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForGrocery->errorCode;
	}
	shaderProgramForChamber = new ShaderProgram("Shaders/Chamber/vertex_shader_of_chamber.glsl", 
		"Shaders/Chamber/fragment_shader_of_chamber.glsl");
	if (shaderProgramForChamber->errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForChamber->errorCode;
	}
	shaderProgramForRefrigerator = new ShaderProgram("Shaders/Refrigerator/vertex_shader_of_refrigerator.glsl", 
		"Shaders/Refrigerator/fragment_shader_of_refrigerator.glsl");
	if (shaderProgramForRefrigerator->errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForRefrigerator->errorCode;
	}
	shaderProgramForNonlogoText = new ShaderProgram("Shaders/NonlogoText/vertex_shader_of_nonlogo_text.glsl", 
		"Shaders/NonlogoText/fragment_shader_of_nonlogo_text.glsl");
	if (shaderProgramForNonlogoText->errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForNonlogoText->errorCode;
	}
	shaderProgramForLogoText = new ShaderProgram("Shaders/LogoText/vertex_shader_of_logo_text.glsl", 
		"Shaders/LogoText/fragment_shader_of_logo_text.glsl");
	if (shaderProgramForLogoText->errorCode != 0)
	{
		glfwTerminate();

		return shaderProgramForLogoText->errorCode;
	}

	// Draw only the lines connecting the vertices. In other words, activate "the wireframe" mode.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Vertices in the normalized device coordinates system (from -1.0F to 1.0F).
	// Since the vertex by itself doesn't have a surface (the vertex is simply a single point in space), its surrounding
	// vertices need to be used to figure out the surface of the vertex in question.
	// A neat trick can be used to calculate the normal vectors for all the cube's vertices by using the cross product.
	// However, the cube is a simple shape, so the normal vectors can simply be manually added to the vertex data.
	// 36 vertices are needed to render the cube (6 sides * 2 triangles per side * 3 vertices for each triangle).
	float verticesOfGroceries[] = {
		// position           // normal vector     // texture coordinates
		// in the freezing chamber
		-0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // left fish sticks package
		-0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // - back side
		-0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		-0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		-0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 
		-0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
		-0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // left fish sticks package
		-0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
		-0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		-0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		-0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
		-0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
		-0.45F, -0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
		-0.45F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
		-0.45F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		-0.45F,  0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		-0.05F, -0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
		-0.05F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
		-0.05F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F,  0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		-0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
		-0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
		-0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
		-0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // left fish sticks package
		-0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
		-0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // right fish sticks package
		 0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // - back side
		 0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		 0.05F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		 0.45F, -0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 
		 0.45F,  0.2F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
		 0.05F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // right fish sticks package
		 0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
		 0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		 0.05F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		 0.45F, -0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
		 0.45F,  0.2F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
		 0.05F, -0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
		 0.05F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
		 0.05F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F,  0.2F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		 0.05F,  0.2F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		 0.45F, -0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
		 0.45F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
		 0.45F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F,  0.2F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F,  0.2F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
		 0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
		 0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.2F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F, -0.2F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // right fish sticks package
		 0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
		 0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F,  0.2F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F,  0.2F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
		// in the refrigerating chamber
		-0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // left milk carton box
		-0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // - back side
		-0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		-0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		-0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 
		-0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
		-0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // left milk carton box
		-0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
		-0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		-0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		-0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
		-0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
		-0.45F, -0.7F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
		-0.45F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
		-0.45F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		-0.45F, -0.3F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		-0.05F, -0.7F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
		-0.05F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
		-0.05F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F, -0.3F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		-0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
		-0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
		-0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
		-0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // left milk carton box
		-0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
		-0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		-0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		-0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
		-0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 0.0F, // right milk carton box
		 0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, // - back side
		 0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		 0.05F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 1.0F, 1.0F, 
		 0.45F, -0.7F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 
		 0.45F, -0.3F,  0.3F,  0.0F,  0.0F, -1.0F, 0.0F, 1.0F, 
		 0.05F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, // right milk carton box
		 0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, // - front side
		 0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		 0.05F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 0.0F, 1.0F, 
		 0.45F, -0.7F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 0.0F, 
		 0.45F, -0.3F,  0.6F,  0.0F,  0.0F,  1.0F, 1.0F, 1.0F, 
		 0.05F, -0.7F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
		 0.05F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - left side
		 0.05F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.3F,  0.3F, -1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.7F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		 0.05F, -0.3F,  0.6F, -1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		 0.45F, -0.7F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
		 0.45F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, // - right side
		 0.45F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.3F,  0.6F,  1.0F,  0.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.7F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F, -0.3F,  0.3F,  1.0F,  0.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
		 0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, // - bottom side
		 0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.7F,  0.3F,  0.0F, -1.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F, -0.7F,  0.6F,  0.0F, -1.0F,  0.0F, 1.0F, 1.0F, 
		 0.05F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, // right milk carton box
		 0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, // - top side
		 0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		 0.05F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 0.0F, 1.0F, 
		 0.45F, -0.3F,  0.6F,  0.0F,  1.0F,  0.0F, 1.0F, 0.0F, 
		 0.45F, -0.3F,  0.3F,  0.0F,  1.0F,  0.0F, 1.0F, 1.0F
	};
	float verticesOfChambers[] = {
		// position           // normal vector     // color
		-0.5F, -0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		 0.5F, -0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side
		-0.5F,  0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F,  0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		 0.5F, -0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side
		-0.5F,  0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F,  0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.24F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		-0.5F, -0.24F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side
		-0.5F,  0.24F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F,  0.24F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.24F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F,  0.24F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		/*
		 0.5F, -0.24F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		 0.5F, -0.24F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side
		 0.5F,  0.24F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.24F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 */
		-0.5F, -0.24F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		 0.5F, -0.24F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side
		-0.5F, -0.24F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.24F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.24F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.24F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 /*
		-0.5F,  0.24F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted freezing chamber plastic
		 0.5F,  0.24F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side
		-0.5F,  0.24F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F,  0.24F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F,  0.24F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 */
		-0.5F, -0.74F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		 0.5F, -0.74F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - back side
		-0.5F, -0.26F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.26F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.74F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F, -0.8F,  0.0F,  0.0F, -1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.74F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		 0.5F, -0.74F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - front side
		-0.5F, -0.26F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.26F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.74F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F,  0.8F,  0.0F,  0.0F,  1.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.74F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		-0.5F, -0.74F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - left side
		-0.5F, -0.26F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.26F, -0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.74F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.26F,  0.8F, -1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		/*
		 0.5F, -0.74F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		 0.5F, -0.74F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - right side
		 0.5F, -0.26F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F,  0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.74F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F, -0.8F,  1.0F,  0.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 */
		-0.5F, -0.74F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		 0.5F, -0.74F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - bottom side
		-0.5F, -0.74F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.74F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.74F, -0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.74F,  0.8F,  0.0F, -1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F/*, 
		-0.5F, -0.26F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // see-through, blue-tinted refrigerating chamber plastic
		 0.5F, -0.26F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, // - top side
		-0.5F, -0.26F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		-0.5F, -0.26F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F,  0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F, 
		 0.5F, -0.26F, -0.8F,  0.0F,  1.0F,  0.0F, 0.0F, 0.0F, 1.0F, 0.25F
		 */
	};
	float verticesOfRefrigerator[] = {
		// position                // normal vector     // color
		  -0.8F,   -0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		   0.8F,   -0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - back side
		  -0.8F,    0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,   -0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,   -1.0F,  0.0F,  0.0F, -1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,   -0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		   0.8F,   -0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - front side
		  -0.8F,    0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,   -0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,    1.0F,  0.0F,  0.0F,  1.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,   -0.8F,   -1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		  -0.8F,   -0.8F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - left side
		  -0.8F,    0.8F,   -1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,   -1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,   -0.8F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,    1.0F, -1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  /*
		   0.8F,   -0.8F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		   0.8F,   -0.8F,   -1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - right side
		   0.8F,    0.8F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,    1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,   -0.8F,   -1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,   -1.0F,  1.0F,  0.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   */
		  -0.8F,   -0.8F,   -1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		   0.8F,   -0.8F,   -1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - bottom side
		  -0.8F,   -0.8F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,   -0.8F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,   -0.8F,   -1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,   -0.8F,    1.0F,  0.0F, -1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // refrigerator
		   0.8F,    0.8F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, // - top side
		  -0.8F,    0.8F,   -1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		  -0.8F,    0.8F,   -1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,    1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		   0.8F,    0.8F,   -1.0F,  0.0F,  1.0F,  0.0F,  0.9F,  0.9F,  0.9F, 0.5F, 
		// (0.1125F + 0.0050F = 0.1175F) * windowWidth, 0.8325F * windowHeight
		-0.775F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.475F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
		-0.775F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.475F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
		-0.775F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.775F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
		-0.775F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
		-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
		-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // digital clock widget
		-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
		-0.775F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.475F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.475F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
		-0.775F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.475F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
		-0.775F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.775F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
		-0.775F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.475F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
		-0.475F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.775F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
		-0.475F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // see-through mode activation button
		-0.475F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
		-0.775F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.775F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.475F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		-0.725F,   0.47F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // rectangle symbol on the see-through mode activation button
		-0.525F,   0.47F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		-0.725F,   0.53F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		-0.525F,   0.53F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.1F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.2F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
		   0.1F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.2F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
		   0.1F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.65F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.1F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
		   0.1F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.2F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
		   0.2F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.2F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
		   0.1F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of freezing chamber temperature widget
		   0.2F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
		   0.1F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.12F,    0.7F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // line representing the "-" sign itself
		  0.18F,    0.7F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		// (0.2250F + 0.4425F = 0.6675F) * windowWidth, 0.8325F * windowHeight
		 0.225F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.625F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
		 0.225F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.625F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
		 0.225F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.625F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.225F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
		 0.225F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.625F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.625F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
		 0.625F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.625F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
		 0.225F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.625F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // freezing chamber temperature widget
		 0.625F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
		 0.225F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.775F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.75F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
		  0.65F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.75F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
		  0.65F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.65F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
		  0.65F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.75F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
		  0.75F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.75F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
		  0.65F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.65F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of freezing chamber temperature widget
		  0.75F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
		  0.65F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.75F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.67F,    0.7F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // lines representing the "+" sign itself
		  0.73F,    0.7F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.7F,   0.67F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.7F,   0.73F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.1F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.2F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
		   0.1F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.2F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
		   0.1F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.1F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
		   0.1F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.2F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
		   0.2F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.2F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
		   0.1F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "-" button, left of refrigerating chamber temperature widget
		   0.2F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
		   0.1F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.1F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		   0.2F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.12F,    0.5F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // line representing the "-" sign itself
		  0.18F,    0.5F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		// (0.2250F + 0.4625F = 0.6875F) * windowWidth, 0.7325F * windowHeight
		 0.225F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.625F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - back side
		 0.225F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.005F,  0.0F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.625F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - front side
		 0.225F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.025F,  0.0F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.425F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.225F,  0.425F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - left side
		 0.225F,  0.575F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.005F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.425F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.025F, -1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.625F,  0.425F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - right side
		 0.625F,  0.575F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.025F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.005F,  1.0F,  0.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.625F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - bottom side
		 0.225F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.005F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.425F,  1.025F,  0.0F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // refrigerating chamber temperature widget
		 0.625F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, // - top side
		 0.225F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.225F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.025F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		 0.625F,  0.575F,  1.005F,  0.0F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.75F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - back side
		  0.65F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.005F,  0.0F,  0.0F, -1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.75F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - front side
		  0.65F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.025F,  0.0F,  0.0F,  1.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.65F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - left side
		  0.65F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.005F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.025F, -1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.75F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - right side
		  0.75F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.025F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.005F,  1.0F,  0.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.75F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - bottom side
		  0.65F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.005F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.45F,  1.025F,  0.0F, -1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // "+" button, right of refrigerating chamber temperature widget
		  0.75F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, // - top side
		  0.65F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.65F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.025F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.75F,   0.55F,  1.005F,  0.0F,  1.0F,  0.0F, 0.75F, 0.75F, 0.75F, 1.0F, 
		  0.67F,    0.5F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, // lines representing the "+" sign itself
		  0.73F,    0.5F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.7F,   0.47F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F, 
		   0.7F,   0.53F,  1.025F,  0.0F,  0.0F,  1.0F,  1.0F,  1.0F,  1.0F, 1.0F
	};

	// Create memory on the GPU where vertex data and index data will be stored.
	// Said data will be handled by VAO and vertex/element buffer objects inside that VAO.
	// Core OpenGL REQUIRES the use of VAOs!
	unsigned int groceriesVAO, chambersVAO, refrigeratorVAO, textVAO;
	glGenVertexArrays(1, &groceriesVAO); glGenVertexArrays(1, &chambersVAO); glGenVertexArrays(1, &refrigeratorVAO);
	glGenVertexArrays(1, &textVAO);
	unsigned int groceriesVBO, chambersVBO, refrigeratorVBO, textVBO;
	glGenBuffers(1, &groceriesVBO); glGenBuffers(1, &chambersVBO); glGenBuffers(1, &refrigeratorVBO);
	glGenBuffers(1, &textVBO);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(groceriesVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, groceriesVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfGroceries), verticesOfGroceries, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 8U * sizeof(float), (void*) 0U);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Normal vector attribute.
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, 8U * sizeof(float), (void*) (3U * sizeof(float)));
	// Enable vertex's normal vector attribute.
	glEnableVertexAttribArray(1U);
	// Texture coordinates attribute.
	glVertexAttribPointer(2U, 2, GL_FLOAT, GL_FALSE, 8U * sizeof(float), (void*) (6U * sizeof(float)));
	// Enable vertex's texture coodinates attribute.
	glEnableVertexAttribArray(2U);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(chambersVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, chambersVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfChambers), verticesOfChambers, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) 0U);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Normal vector attribute.
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) (3U * sizeof(float)));
	// Enable vertex's normal vector attribute.
	glEnableVertexAttribArray(1U);
	// Color attribute.
	glVertexAttribPointer(2U, 4, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) (6U * sizeof(float)));
	// Enable vertex's color attribute.
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
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) 0U);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);
	// Normal vector attribute.
	glVertexAttribPointer(1U, 3, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) (3U * sizeof(float)));
	// Enable vertex's normal vector attribute.
	glEnableVertexAttribArray(1U);
	// Color attribute.
	glVertexAttribPointer(2U, 4, GL_FLOAT, GL_FALSE, 10U * sizeof(float), (void*) (6U * sizeof(float)));
	// Enable vertex's color attribute.
	glEnableVertexAttribArray(2U);

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

	// Generate textures, set their wrapping and filtering parameters, load the images-to-become-textures from
	// the file system and generate all the required mipmaps using the helper class.
	Texture fishSticksPackage("Resources/Images/Fish_sticks_package.png");
	if (fishSticksPackage.errorCode)
	{
		glfwTerminate();

		return fishSticksPackage.errorCode;
	}
	Texture milkCartonBox("Resources/Images/Milk_carton_box.png");
	if (milkCartonBox.errorCode)
	{
		glfwTerminate();

		return milkCartonBox.errorCode;
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

	// Create the camera with the specified position, front vector and up vector using the helper "Camera" class.
	camera = new Camera(glm::vec3(0.0F, 0.0F, 3.0F), glm::vec3(0.0F, 0.0F, -1.0F), glm::vec3(0.0F, 1.0F, 0.0F));

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
		std::cout << "-------------------------" << std::endl;
		std::cout << "             Delta time: " << deltaTime << " s." << std::endl;
		std::cout << " Frame rate (1 / delta): " << frameRate << " s^(-1)." << std::endl;
		std::cout << "    Previous frame time: " << previousFrameTime << " s." << std::endl;

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
			// glDrawArrays(GL_TRIANGLES, 0, 36);  // see-through, blue-tinted freezing chamber plastic
			glDrawArrays(GL_TRIANGLES, 0, 30);  // see-through, blue-tinted freezing chamber plastic
			// glDrawArrays(GL_TRIANGLES, 36, 36); // see-through, blue-tinted refrigerating chamber plastic
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

			// Bind (assign) the desired VAO to OpenGL's context.
			glBindVertexArray(refrigeratorVAO);
			// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
			glDrawArrays(GL_TRIANGLES, 0, 36);   // refrigerator doors

			// Always turn on the blending when rendering the graphical elements and text, due to the way the "FreeType"
			// library is implemented.
			glEnable(GL_BLEND);

			glDrawArrays(GL_TRIANGLES, 36, 36);  // digital clock rectangle widget
			glDrawArrays(GL_TRIANGLES, 72, 36);  // see-through mode activation button
			glDrawArrays(GL_TRIANGLES, 108, 36); // rectangle symbol on the see-through mode activation button
			glDrawArrays(GL_TRIANGLES, 144, 36); // "-" button, left of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 170, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 172, 36); // freezing chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 208, 36); // "+" button, left of freezing chamber temperature widget
			glDrawArrays(GL_LINES, 244, 4);      // line representing the "+" sign itself
			glDrawArrays(GL_TRIANGLES, 248, 36); // "-" button, left of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 284, 2);      // line representing the "-" sign itself
			glDrawArrays(GL_TRIANGLES, 286, 36); // refrigerating chamber temperature widget
			glDrawArrays(GL_TRIANGLES, 322, 36); // "+" button, left of refrigerating chamber temperature widget
			glDrawArrays(GL_LINES, 358, 4);      // line representing the "+" sign itself

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
			struct tm* timeInfo;
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
				0.1175F * windowWidth, 0.8325F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

			std::string currentTemperatureOfFreezingChamberAsString = 
				std::to_string(currentTemperatureOfFreezingChamber);
			currentTemperatureOfFreezingChamberAsString = currentTemperatureOfFreezingChamberAsString
				.substr(0, currentTemperatureOfFreezingChamberAsString.size() - 5U);
			// Render the current temperature of the freezing chamber in its widget's space, scale it 2/3 times and
			// paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, currentTemperatureOfFreezingChamberAsString, 
				0.6675F * windowWidth, 0.8325F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

			std::string currentTemperatureOfRefrigeratingChamberAsString = 
				std::to_string(currentTemperatureOfRefrigeratingChamber);
			currentTemperatureOfRefrigeratingChamberAsString = currentTemperatureOfRefrigeratingChamberAsString
				.substr(0, currentTemperatureOfRefrigeratingChamberAsString.size() - 5U);
			// Render the current temperature of the refrigerating chamber in its widget's space, scale it 2/3 times and
			// paint it white.
			timesNewRomanFont.renderText(*shaderProgramForNonlogoText, currentTemperatureOfRefrigeratingChamberAsString, 
				0.6875F * windowWidth, 0.7325F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

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
	// De-allocate shader programs using their destructors.
	delete shaderProgramForLogoText;
	delete shaderProgramForNonlogoText;
	delete shaderProgramForRefrigerator;
	delete shaderProgramForChamber;
	delete shaderProgramForGrocery;

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
			// Tell the GLFW library to capture and hide the mouse cursor. Capturing the mouse cursor means fixating it
			// to the center of the application's window and only letting it move if the application loses focus or quits.
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			return;
		}

		if (graphicalModeTurnedOn)
		{
			// Update the graphical mode activation timestamp with the current time on every left click.
			timeWhenGraphicalModeWasActivated = static_cast<float>(glfwGetTime());

			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			// std::cout << "Cursor pos (x, y): (" << xpos << ", " << ypos << ")." << std::endl;

			// see-through mode activation button
			if (xpos >= 0.1125 * windowWidth && xpos <= 0.2625 * windowWidth 
				&& ypos >= 0.225 * windowHeight && ypos <= 0.275 * windowHeight)
			{
				// Activate the desired shader program.
				// Every shader and rendering call from now on will use this shader program object.
				shaderProgramForChamber->useProgram();

				// Update see-through mode global variable and uniform.
				seeThroughModeTurnedOn = !seeThroughModeTurnedOn;
				shaderProgramForChamber->setBoolUniform("seeThroughModeTurnedOn", seeThroughModeTurnedOn);

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
			if (xpos >= 0.55 * windowWidth && xpos <= 0.6 * windowWidth 
				&& ypos >= 0.125 * windowHeight && ypos <= 0.175 * windowHeight)
			{
				currentTemperatureOfFreezingChamber -= temperatureOffset;
				if (currentTemperatureOfFreezingChamber < minTemperatureOfFreezingChamber)
				{
					currentTemperatureOfFreezingChamber = minTemperatureOfFreezingChamber;
				}

				return;
			}
			// "+" button, right of freezing chamber temperature widget
			if (xpos >= 0.825 * windowWidth && xpos <= 0.875 * windowWidth 
				&& ypos >= 0.125 * windowHeight && ypos <= 0.175 * windowHeight)
			{
				currentTemperatureOfFreezingChamber += temperatureOffset;
				if (currentTemperatureOfFreezingChamber > maxTemperatureOfFreezingChamber)
				{
					currentTemperatureOfFreezingChamber = maxTemperatureOfFreezingChamber;
				}

				return;
			}
			// "-" button, left of refrigerating chamber temperature widget
			if (xpos >= 0.55 * windowWidth && xpos <= 0.6 * windowWidth 
				&& ypos >= 0.225 * windowHeight && ypos <= 0.275 * windowHeight)
			{
				currentTemperatureOfRefrigeratingChamber -= temperatureOffset;
				if (currentTemperatureOfRefrigeratingChamber < minTemperatureOfRefrigeratingChamber)
				{
					currentTemperatureOfRefrigeratingChamber = minTemperatureOfRefrigeratingChamber;
				}

				return;
			}
			// "+" button, right of refrigerating chamber temperature widget
			if (xpos >= 0.825 * windowWidth && xpos <= 0.875 * windowWidth 
				&& ypos >= 0.225 * windowHeight && ypos <= 0.275 * windowHeight)
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
		// Move the camera.
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
