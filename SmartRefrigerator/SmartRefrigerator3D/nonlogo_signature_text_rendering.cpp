#include "nonlogo_signature_text_rendering.hpp"

void renderNonlogoSignatureText()
{
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
	glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
	// Unbind UBO for safety reasons.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);

	// Set the current window width uniform.
	shaderProgramForNonlogoText->setFloatUniform("windowWidth", static_cast<float>(windowWidth));

	// Render the author's signature in the bottom left corner of the screen space, scale it 2/3 times and paint it
	// yellow.
	timesNewRomanFont->renderText(*shaderProgramForNonlogoText, "Darijan Micic, RA 203/2017", 
		glm::max(0.0125F * windowWidth, 10.0F), glm::max(0.016667F * windowHeight, 10.0F), 
		0.666667F, glm::vec3(1.0F, 1.0F, 0.0F));
}
