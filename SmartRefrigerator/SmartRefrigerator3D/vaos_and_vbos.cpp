#include "vaos_and_vbos.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here
unsigned int groceriesVAO;
unsigned int chambersVAO;
unsigned int refrigeratorVAO;
unsigned int refrigeratorDoorsVAO;
unsigned int lightSourceInsideRefrigeratorVAO;
unsigned int textVAO;
unsigned int groceriesVBO;
unsigned int chambersVBO;
unsigned int refrigeratorVBO;
unsigned int refrigeratorDoorsVBO;
unsigned int lightSourceInsideRefrigeratorVBO;
unsigned int textVBO;

void generateVertexArraysAndBuffers()
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
}

void unbindVBOAndVAOForSafetyReasons()
{
	// Unbind VBO and VAO for safety reasons. This is not neccessary.
	// VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER.
	// This also means it stores its unbind calls, so
	// DO NOT EVER unbind EBO before unbinding VAO, otherwise it won't have a configured EBO.
	glBindBuffer(GL_ARRAY_BUFFER, 0U);
	glBindVertexArray(0U);
}

void setUpVAOsAndVBOs()
{
	generateVertexArraysAndBuffers();
	copyUserDefinedDataToGPUAndTellOpenGLHowItShouldInterpretIt();
	unbindVBOAndVAOForSafetyReasons();
}
