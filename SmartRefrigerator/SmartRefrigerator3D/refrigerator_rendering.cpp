#include "refrigerator_rendering.hpp"

void renderRefrigerator()
{
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForRefrigerator->useProgram();

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

	// The model matrix transforms the local-space coordinates to the world-space coordinates.
	modelMatrix = glm::mat4(1.0F);
	// The refrigerator is 0.15F FURTHER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, -0.15F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36);   // refrigerator (back side)
	glDrawArrays(GL_TRIANGLES, 36, 36);  // refrigerator (left side)
	glDrawArrays(GL_TRIANGLES, 72, 36);  // refrigerator (right side)
	glDrawArrays(GL_TRIANGLES, 108, 36); // refrigerator (bottom side)
	glDrawArrays(GL_TRIANGLES, 144, 36); // refrigerator (top side)
}
