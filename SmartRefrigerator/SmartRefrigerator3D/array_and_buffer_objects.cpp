#include "array_and_buffer_objects.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

unsigned int groceriesVAO = 0U;
unsigned int chambersVAO = 0U;
unsigned int refrigeratorVAO = 0U;
unsigned int refrigeratorDoorsVAO = 0U;
unsigned int lightSourceInsideRefrigeratorVAO = 0U;
unsigned int textVAO = 0U;
unsigned int groceriesVBO = 0U;
unsigned int chambersVBO = 0U;
unsigned int refrigeratorVBO = 0U;
unsigned int refrigeratorDoorsVBO = 0U;
unsigned int lightSourceInsideRefrigeratorVBO = 0U;
unsigned int textVBO = 0U;
unsigned int viewAndProjectionMatricesUBO = 0U;
unsigned int projectionMatrixUBO = 0U;

void generateArrayAndBufferObjects()
{
	// Create memory on the GPU where vertex data and index data will be stored.
	// Said data will be handled by VAO and vertex/element buffer objects inside that VAO.
	// Core OpenGL REQUIRES the use of VAOs!
	glGenVertexArrays(1, &groceriesVAO);
	glGenVertexArrays(1, &chambersVAO);
	glGenVertexArrays(1, &refrigeratorVAO);
	glGenVertexArrays(1, &refrigeratorDoorsVAO);
	glGenVertexArrays(1, &lightSourceInsideRefrigeratorVAO);
	glGenVertexArrays(1, &textVAO);

	glGenBuffers(1, &groceriesVBO);
	glGenBuffers(1, &chambersVBO);
	glGenBuffers(1, &refrigeratorVBO);
	glGenBuffers(1, &refrigeratorDoorsVBO);
	glGenBuffers(1, &lightSourceInsideRefrigeratorVBO);
	glGenBuffers(1, &textVBO);

	glGenBuffers(1, &viewAndProjectionMatricesUBO);
	glGenBuffers(1, &projectionMatrixUBO);
}

void copyUserDefinedDataToGPUAndTellOpenGLHowItShouldInterpretIt()
{
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
	glBindVertexArray(refrigeratorDoorsVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, refrigeratorDoorsVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfRefrigeratorDoors), verticesOfRefrigeratorDoors, GL_STATIC_DRAW);
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
	glBindVertexArray(lightSourceInsideRefrigeratorVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, lightSourceInsideRefrigeratorVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesOfLightSourceInsideRefrigerator), 
		verticesOfLightSourceInsideRefrigerator, GL_STATIC_DRAW);
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position attribute.
	glVertexAttribPointer(0U, 3, GL_FLOAT, GL_FALSE, 3U * sizeof(float), (void*) 0U);
	// Enable vertex's position attribute.
	glEnableVertexAttribArray(0U);

	// Bind (assign) the newly created VAO to OpenGL's context.
	glBindVertexArray(textVAO);
	// Bind (assign) the newly created VBO to OpenGL's context.
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	// Copy user-defined data into the currently bound buffer.
	// Vertex data is now stored on the graphics card's memory.
	glBufferData(GL_ARRAY_BUFFER, 6U * 4U * sizeof(float), (void*) 0U, GL_DYNAMIC_DRAW); // For often updates of the content.
	// Tell OpenGL how it should interpret vertex data, per vertex attribute.
	// Position and texture coordinates (combined) attribute.
	glVertexAttribPointer(0U, 4, GL_FLOAT, GL_FALSE, 4U * sizeof(float), (void*) 0U);
	// Enable vertex's position and texture coordinates (combined) attribute.
	glEnableVertexAttribArray(0U);

	// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL

	// Bind (assign) the newly created UBO to OpenGL's context.
	glBindBuffer(GL_UNIFORM_BUFFER, viewAndProjectionMatricesUBO);
	// Allocate enough space in graphics card's memory to hold contents of this UBO.
	glBufferData(GL_UNIFORM_BUFFER, 2U * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	// Bind the binding point to its UBO (the one currently set up).
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);
	// Bind the UBO to its binding point using either the "glBindBufferBase()" function or the
	// "glBindBufferRange()" function. From this point on, both sides of the binding point are linked.
	// "glBindbufferBase()" function expects a target, a binding point index and a UBO.
	// "glBindBufferRange()" function enables linking multiple different uniform blocks to a single UBO.
	glBindBufferRange(GL_UNIFORM_BUFFER, 0U, viewAndProjectionMatricesUBO, 0, 2U * sizeof(glm::mat4));

	// Bind (assign) the newly created UBO to OpenGL's context.
	glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
	// Allocate enough space in graphics card's memory to hold contents of this UBO.
	glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	// Bind the binding point to its UBO (the one currently set up).
	glBindBuffer(GL_UNIFORM_BUFFER, 1U);
	// Bind the UBO to its binding point using either the "glBindBufferBase()" function or the
	// "glBindBufferRange()" function. From this point on, both sides of the binding point are linked.
	// "glBindbufferBase()" function expects a target, a binding point index and a UBO.
	// "glBindBufferRange()" function enables linking multiple different uniform blocks to a single UBO.
	glBindBufferRange(GL_UNIFORM_BUFFER, 1U, projectionMatrixUBO, 0, sizeof(glm::mat4));
}

void unbindArrayAndBufferObjectsForSafetyReasons()
{
	// Unbind UBO, VBO and VAO for safety reasons. This is not neccessary.
	// VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
	// This also means it stores its unbind calls, so
	// DO NOT EVER unbind EBO before unbinding VAO, otherwise it won't have a configured EBO.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);
	glBindBuffer(GL_ARRAY_BUFFER, 0U);
	glBindVertexArray(0U);
}

void setUpArrayAndBufferObjects()
{
	generateArrayAndBufferObjects();
	copyUserDefinedDataToGPUAndTellOpenGLHowItShouldInterpretIt();
	unbindArrayAndBufferObjectsForSafetyReasons();
}
