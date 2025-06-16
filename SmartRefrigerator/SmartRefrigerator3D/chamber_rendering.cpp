#include "chamber_rendering.hpp"

void renderChamber()
{
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
	modelMatrix = glm::mat4(1.0F);
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
	glBindVertexArray(chamberVAO);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 180);   // see-through, blue-tinted freezing chamber plastic

	// The refrigerating chamber is 0.5F BELOW the freezing chamber.
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, -0.5F, 0.0F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 180); // see-through, blue-tinted refrigerating chamber plastic
}
