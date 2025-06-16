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
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Set the see-through mode uniform.
	shaderProgramForChamber->setBoolUniform("seeThroughModeTurnedOn", seeThroughModeTurnedOn);
	// Set the current window width and height uniforms.
	shaderProgramForChamber->setFloatUniform("windowWidth", static_cast<float>(windowWidth));
	shaderProgramForChamber->setFloatUniform("windowHeight", static_cast<float>(windowHeight));
	// Set the current temperatures of each chamber uniforms.
	shaderProgramForChamber->setFloatUniform(
		"currentTemperatureOfFreezingChamber", currentTemperatureOfFreezingChamber);
	shaderProgramForChamber->setFloatUniform(
		"currentTemperatureOfRefrigeratingChamber", currentTemperatureOfRefrigeratingChamber);

	// Set the is scene lit uniform.
	shaderProgramForChamber->setBoolUniform("sceneLit", sceneLit);
	if (sceneLit)
	{
		// REFERENCE: https://learnopengl.com/Lighting/Light-casters
		// Set position of viewer to field "position" of global object "camera".
		shaderProgramForChamber->setFloatVec3Uniform("positionOfViewer", camera->position);

		// Set the spotlight inside refrigerator uniforms.
		shaderProgramForChamber->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.direction", glm::vec3(0.0F, 0.0F, 1.0F));
		shaderProgramForChamber->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.position", glm::vec3(0.0F, 0.6F, -0.995F));
		shaderProgramForChamber->setFloatUniform(
			"lightSourceInsideRefrigerator.cosOfInnerCutoffAngle", glm::cos(glm::radians(20.0F)));
		shaderProgramForChamber->setFloatUniform(
			"lightSourceInsideRefrigerator.cosOfOuterCutoffAngle", glm::cos(glm::radians(30.0F)));
		float blueColorComponentOfLight =
			(currentAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator) / 
				(maxAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator);
		shaderProgramForChamber->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.ambientColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
		shaderProgramForChamber->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.diffuseColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
		shaderProgramForChamber->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.specularColor", glm::vec3(1.0F, 1.0F, 1.0F));
		// REFERENCE: https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
		// REFERENCE: https://wiki.ogre3d.org/Light%20Attenuation%20Shortcut
		// kC = 1.0F, kL = 4.5F / d, kQ = 75.0F / d^2; d = 5.0F
		shaderProgramForChamber->setFloatUniform("lightSourceInsideRefrigerator.kC", 1.0F);
		shaderProgramForChamber->setFloatUniform("lightSourceInsideRefrigerator.kL", 0.9F);
		shaderProgramForChamber->setFloatUniform("lightSourceInsideRefrigerator.kQ", 3.0F);

		// Set the shininess of the specular highlight. Shininess value of highlight (the light source's beam)
		// determines the size (radius) and the scattering of specular highlight. This value should be a degree
		// of number 2 (2, 4, 8, 16, 32, ...).
		// Higher value results in a smaller, focused specular highlight. The light is reflected more properly.
		// Lower value results in a larger, scattered specular highlight. The light is reflected less properly.
		float shininessOfSpecularHighlight = 4.0F;
		shaderProgramForChamber->setFloatUniform(
			"material.shininessOfSpecularHighlight", shininessOfSpecularHighlight);
	}
	// Set the current intensity of background light uniform.
	shaderProgramForChamber->setFloatUniform("intensityOfBackgroundLight", intensityOfBackgroundLight);

	// Bind (assign) the desired VAO to OpenGL's context.
	glBindVertexArray(chamberVAO);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 216);   // see-through, blue-tinted freezing chamber plastic

	// The refrigerating chamber is 0.5F BELOW the freezing chamber.
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, -0.5F, 0.0F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 216); // see-through, blue-tinted refrigerating chamber plastic
}
