#include "light_source_inside_refrigerator_rendering.hpp"

void renderLightSourceInsideRefrigerator()
{
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForLightSourceInsideRefrigerator->useProgram();

	// Set the current temperatures of refrigerator uniform.
	shaderProgramForLightSourceInsideRefrigerator->setFloatUniform(
		"currentAvgTemperatureOfRefrigerator", currentAvgTemperatureOfRefrigerator);

	// Bind (assign) the desired VAO to OpenGL's context.
	glBindVertexArray(lightSourceInsideRefrigeratorVAO);

	// The model matrix transforms the local-space coordinates to the world-space coordinates.
	modelMatrix = glm::mat4(1.0F);
	// The light source inside refrigerator is 0.6F ABOVE and 1.045F FURTHER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.6F, -1.045F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForLightSourceInsideRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36); // light source inside refrigerator
}
