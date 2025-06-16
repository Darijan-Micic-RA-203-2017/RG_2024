#include "logo_text_rendering.hpp"

void renderLogoText()
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
	glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
	// Unbind UBO for safety reasons.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);

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
	timesNewRomanFont->renderText(*shaderProgramForLogoText, "LOK", 
		bottomLeftXOfLogoText, bottomLeftYOfLogoText, 4.0F, glm::vec3(0.0F, 0.0F, 1.0F));
}
