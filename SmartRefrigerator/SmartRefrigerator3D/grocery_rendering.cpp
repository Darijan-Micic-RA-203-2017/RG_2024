#include "grocery_rendering.hpp"

void renderGrocery()
{
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForGrocery->useProgram();

	// Activate the texture unit (one of 16). After activating a texture unit, a subsequent "glBindTexture"
	// call will bind that texture to the currently active texture unit. The texture unit "GL_TEXTURE0" is
	// always active by default, so it isn't necessary to manually activate any texture unit if only one texture
	// is used.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fishSticksPackage->id);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, milkCartonBox->id);

	currentAvgTemperatureOfRefrigerator = 
		(currentTemperatureOfFreezingChamber + currentTemperatureOfRefrigeratingChamber) / 2.0F;
	// Set the is scene lit uniform.
	shaderProgramForGrocery->setBoolUniform("sceneLit", sceneLit);
	if (sceneLit)
	{
		// REFERENCE: https://learnopengl.com/Lighting/Light-casters
		// Set position of viewer to field "position" of global object "camera".
		shaderProgramForGrocery->setFloatVec3Uniform("positionOfViewer", camera->position);

		// Set the spotlight inside refrigerator uniforms.
		shaderProgramForGrocery->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.direction", glm::vec3(0.0F, 0.0F, 1.0F));
		shaderProgramForGrocery->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.position", glm::vec3(0.0F, 0.6F, -0.995F));
		shaderProgramForGrocery->setFloatUniform(
			"lightSourceInsideRefrigerator.cosOfInnerCutoffAngle", glm::cos(glm::radians(20.0F)));
		shaderProgramForGrocery->setFloatUniform(
			"lightSourceInsideRefrigerator.cosOfOuterCutoffAngle", glm::cos(glm::radians(30.0F)));
		float blueColorComponentOfLight =
			(currentAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator) / 
				(maxAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator);
		shaderProgramForGrocery->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.ambientColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
		shaderProgramForGrocery->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.diffuseColor", glm::vec3(1.0F, 1.0F, blueColorComponentOfLight));
		shaderProgramForGrocery->setFloatVec3Uniform(
			"lightSourceInsideRefrigerator.specularColor", glm::vec3(1.0F, 1.0F, 1.0F));
		// REFERENCE: https://wiki.ogre3d.org/tiki-index.php?page=-Point+Light+Attenuation
		// REFERENCE: https://wiki.ogre3d.org/Light%20Attenuation%20Shortcut
		// kC = 1.0F, kL = 4.5F / d, kQ = 75.0F / d^2; d = 5.0F
		shaderProgramForGrocery->setFloatUniform("lightSourceInsideRefrigerator.kC", 1.0F);
		shaderProgramForGrocery->setFloatUniform("lightSourceInsideRefrigerator.kL", 0.9F);
		shaderProgramForGrocery->setFloatUniform("lightSourceInsideRefrigerator.kQ", 3.0F);

		// Set the shininess of the specular highlight. Shininess value of highlight (the light source's beam)
		// determines the size (radius) and the scattering of specular highlight. This value should be a degree
		// of number 2 (2, 4, 8, 16, 32, ...).
		// Higher value results in a smaller, focused specular highlight. The light is reflected more properly.
		// Lower value results in a larger, scattered specular highlight. The light is reflected less properly.
		float shininessOfSpecularHighlight = 16.0F;
		shaderProgramForGrocery->setFloatUniform(
			"material.shininessOfSpecularHighlight", shininessOfSpecularHighlight);
	}
	// Set the current intensity of background light uniform.
	shaderProgramForGrocery->setFloatUniform("intensityOfBackgroundLight", intensityOfBackgroundLight);

	// The projection matrix transforms the view-space coordinates to the clip-space coordinates.
	// The projection that will be used is the perspective projection with the varying field of view (FOV) that
	// the user sets by scrolling, 0.1F near plane and 100.0F far plane. The ratio of the window's width and
	// height is called the aspect ratio.
	projectionMatrix = glm::perspective(glm::radians(camera->fov), 
		static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1F, 100.0F);
	// Set the projection matrix. This matrix changes each frame.
	glBindBuffer(GL_UNIFORM_BUFFER, viewAndProjectionMatricesUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix[0U][0U]);
	// Unbind UBO for safety reasons.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);

	// The view matrix transforms the world-space coordinates to the view-space coordinates.
	// The world (scene) will be transformed by moving the camera using the keyboard.
	viewMatrix = camera->getCalculatedViewMatrix();
	// Set the view matrix. This matrix changes each frame.
	glBindBuffer(GL_UNIFORM_BUFFER, viewAndProjectionMatricesUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &viewMatrix[0U][0U]);
	// Unbind UBO for safety reasons.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);

	// Bind (assign) the desired VAO to OpenGL's context.
	glBindVertexArray(groceryVAO);

	// Set the grocery inside freezer uniform.
	groceryInsideFreezer = !groceryInsideFreezer;
	shaderProgramForGrocery->setBoolUniform("groceryInsideFreezer", groceryInsideFreezer);

	// The model matrix transforms the local-space coordinates to the world-space coordinates.
	modelMatrix = glm::mat4(1.0F);
	// The left fish sticks package is 0.25F TO THE LEFT and 0.45F CLOSER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25F, 0.0F, 0.45F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36); // left fish sticks package

	// The right fish sticks package is 0.5F TO THE RIGHT of the left fish sticks package.
	modelMatrix = glm::mat4(1.0F);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5F, 0.0F, 0.0F));
	// The left fish sticks package is 0.25F TO THE LEFT and 0.45F CLOSER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25F, 0.0F, 0.45F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36); // right fish sticks package

	// Set the grocery inside freezer uniform.
	groceryInsideFreezer = !groceryInsideFreezer;
	shaderProgramForGrocery->setBoolUniform("groceryInsideFreezer", groceryInsideFreezer);

	// The right milk carton box is 0.5F BELOW the right fish sticks package.
	// Its width and depth are scaled DOWN 2 times.
	modelMatrix = glm::mat4(1.0F);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5F, -0.5F, 0.0F));
	// The left fish sticks package is 0.25F TO THE LEFT and 0.45F CLOSER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25F, 0.0F, 0.45F));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5F, 1.0F, 0.5F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36); // right milk carton box

	// The left milk carton box is 0.5F TO THE LEFT of the right milk carton box.
	// Its width and depth are scaled DOWN 2 times.
	modelMatrix = glm::mat4(1.0F);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, -0.5F, 0.0F));
	// The left fish sticks package is 0.25F TO THE LEFT and 0.45F CLOSER of the (0.0F, 0.0F, 0.0F).
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25F, 0.0F, 0.45F));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5F, 1.0F, 0.5F));
	// Set the model matrix. This matrix changes each frame.
	shaderProgramForChamber->setFloatMat4Uniform("modelMatrix", modelMatrix);
	// The normal matrix is a model matrix specifically tailored for normal vectors.
	normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	// Set the normal matrix. This matrix changes each frame.
	shaderProgramForGrocery->setFloatMat3Uniform("normalMatrix", normalMatrix);

	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36); // left milk carton box
}
