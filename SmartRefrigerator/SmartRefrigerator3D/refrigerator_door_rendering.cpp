#include "refrigerator_door_rendering.hpp"

void renderRefrigeratorDoor()
{
	if (doorState == DoorState::OPENING)
	{
		// The model matrix transforms the local-space coordinates to the world-space coordinates.
		modelMatrix = glm::mat4(1.0F);
		doorXTranslation += 0.2F * deltaTime;
		if (doorXTranslation > maxDoorXTranslation)
		{
			doorXTranslation = maxDoorXTranslation;
		}
		doorZTranslation += 0.2F * deltaTime;
		if (doorZTranslation > maxDoorZTranslation)
		{
			doorZTranslation = maxDoorZTranslation;
		}
		modelMatrix = glm::translate(modelMatrix, glm::vec3(doorXTranslation, 0.0F, doorZTranslation));
		// The refrigerator door is 1.0875F CLOSER of the (0.0F, 0.0F, 0.0F).
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, 1.0875F));
		doorAngle += 0.2F * deltaTime;
		if (doorAngle > maxDoorAngle)
		{
			doorAngle = maxDoorAngle;
			doorState = DoorState::OPEN;
		}
		modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
		// Set the model matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

		// The normal matrix is a model matrix specifically tailored for normal vectors.
		normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
		// Set the normal matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
	}
	else if (doorState == DoorState::CLOSING)
	{
		// The model matrix transforms the local-space coordinates to the world-space coordinates.
		modelMatrix = glm::mat4(1.0F);
		doorXTranslation -= 0.2F * deltaTime;
		if (doorXTranslation < minDoorXTranslation)
		{
			doorXTranslation = minDoorXTranslation;
		}
		doorZTranslation -= 0.2F * deltaTime;
		if (doorZTranslation < minDoorZTranslation)
		{
			doorZTranslation = minDoorZTranslation;
		}
		modelMatrix = glm::translate(modelMatrix, glm::vec3(doorXTranslation, 0.0F, doorZTranslation));
		// The refrigerator door is 1.0875F CLOSER of the (0.0F, 0.0F, 0.0F).
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, 1.0875F));
		doorAngle -= 0.2F * deltaTime;
		if (doorAngle < minDoorAngle)
		{
			doorAngle = minDoorAngle;
			doorState = DoorState::CLOSED;
		}
		modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
		// Set the model matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

		// The normal matrix is a model matrix specifically tailored for normal vectors.
		normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
		// Set the normal matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
	}
	else if (doorState == DoorState::OPEN)
	{
		// The model matrix transforms the local-space coordinates to the world-space coordinates.
		modelMatrix = glm::mat4(1.0F);
		doorXTranslation = maxDoorXTranslation;
		doorZTranslation = maxDoorZTranslation;
		modelMatrix = glm::translate(modelMatrix, glm::vec3(doorXTranslation, 0.0F, doorZTranslation));
		// The refrigerator door is 1.0875F CLOSER of the (0.0F, 0.0F, 0.0F).
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, 1.0875F));
		doorAngle = maxDoorAngle;
		modelMatrix = glm::rotate(modelMatrix, doorAngle, glm::vec3(0.0F, 1.0F, 0.0F));
		// Set the model matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

		// The normal matrix is a model matrix specifically tailored for normal vectors.
		normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
		// Set the normal matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
	}
	else
	{
		// Scene should not be lit if the door is closed, unless the see-through mode is turned on.
		if (!seeThroughModeTurnedOn)
		{
			sceneLit = false;
		}

		// The model matrix transforms the local-space coordinates to the world-space coordinates.
		modelMatrix = glm::mat4(1.0F);
		// The refrigerator door is 1.0875F CLOSER of the (0.0F, 0.0F, 0.0F).
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0F, 0.0F, 1.0875F));
		// Set the model matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat4Uniform("modelMatrix", modelMatrix);

		// The normal matrix is a model matrix specifically tailored for normal vectors.
		normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
		// Set the normal matrix. This matrix changes each frame.
		shaderProgramForRefrigerator->setFloatMat3Uniform("normalMatrix", normalMatrix);
	}

	// Bind (assign) the desired VAO to OpenGL's context.
	glBindVertexArray(refrigeratorDoorVAO);
	// Parameters: primitive; index of first vertex to be drawn; total number of vertices to be drawn.
	glDrawArrays(GL_TRIANGLES, 0, 36);    // refrigerator (front side)

	// Always turn on the blending when rendering the graphical elements and text, due to the way the
	// "FreeType" library is implemented.
	glEnable(GL_BLEND);

	glDrawArrays(GL_TRIANGLES, 36, 36);  // digital clock rectangle widget
	glDrawArrays(GL_TRIANGLES, 72, 36);  // see-through mode activation button
	glDrawArrays(GL_TRIANGLES, 108, 6);  // rectangle symbol on the see-through mode activation button
	glDrawArrays(GL_TRIANGLES, 114, 36); // door handle, base
	glDrawArrays(GL_TRIANGLES, 150, 36); // door handle, lower connector
	glDrawArrays(GL_TRIANGLES, 186, 36); // door handle, upper connector
	glDrawArrays(GL_TRIANGLES, 222, 36); // door handle, actual handle
	glDrawArrays(GL_TRIANGLES, 258, 36); // "-" button, left of freezing chamber temperature widget
	glDrawArrays(GL_LINES, 294, 2);      // line representing the "-" sign itself
	glDrawArrays(GL_TRIANGLES, 296, 36); // freezing chamber temperature widget
	glDrawArrays(GL_TRIANGLES, 332, 36); // "+" button, right of freezing chamber temperature widget
	glDrawArrays(GL_LINES, 368, 4);      // lines representing the "+" sign itself
	glDrawArrays(GL_TRIANGLES, 372, 36); // "-" button, left of refrigerating chamber temperature widget
	glDrawArrays(GL_LINES, 408, 2);      // line representing the "-" sign itself
	glDrawArrays(GL_TRIANGLES, 410, 36); // refrigerating chamber temperature widget
	glDrawArrays(GL_TRIANGLES, 446, 36); // "+" button, right of refrigerating chamber temperature widget
	glDrawArrays(GL_LINES, 482, 4);      // lines representing the "+" sign itself
	glDrawArrays(GL_TRIANGLES, 486, 36); // "-" button, left of point light intensity widget
	glDrawArrays(GL_LINES, 522, 2);      // line representing the "-" sign itself
	glDrawArrays(GL_TRIANGLES, 524, 36); // point light intensity widget
	glDrawArrays(GL_TRIANGLES, 560, 36); // "+" button, right of point light intensity widget
	glDrawArrays(GL_LINES, 596, 4);      // lines representing the "+" sign itself
}
