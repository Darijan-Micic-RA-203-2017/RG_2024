#include "nonlogo_readings_text_rendering.hpp"

void renderNonlogoReadingsText()
{
	// Activate the desired shader program.
	// Every shader and rendering call from now on will use this shader program object.
	shaderProgramForNonlogoText->useProgram();

	// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic
	// projection matrix will suffice. Using an orthographic projection matrix also allows all vertex coordinates to
	// be specified in screen-space coordinates. In order to take advantage of this, the projection matrix needs to
	// be set up this way: glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
	// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen
	// (0.0F) to the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the
	// bottom-left corner.
	projectionMatrix = glm::ortho(0.0F, static_cast<float>(windowWidth), 0.0F, static_cast<float>(windowHeight));
	// Set the projection matrix. This matrix changes each frame.
	glBindBuffer(GL_UNIFORM_BUFFER, projectionMatrixUBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0U][0U]);
	// Unbind UBO for safety reasons.
	glBindBuffer(GL_UNIFORM_BUFFER, 0U);

	// REFERENCE: https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/localtime-s-localtime32-s-localtime64-s?view=msvc-170
	struct tm time;
	char am_pm[] = "AM";
	__time64_t longTime;
	errno_t err;
	// Get time as 64-bit integer.
	_time64(&longTime);
	// Convert to local time.
	err = _localtime64_s(&time, &longTime);
	if (err)
	{
		return;
	}
	int hours = time.tm_hour;
	// Set up extension.
	if (hours > 12)
	{
		strcpy_s(am_pm, sizeof(am_pm), "PM");
	}
	int minutes = time.tm_min;
	int seconds = time.tm_sec;
	std::string hoursAsString = std::to_string(hours);
	if (hours < 10)
	{
		hoursAsString.insert(0, "0");
	}
	std::string minutesAsString = std::to_string(minutes);
	if (minutes < 10)
	{
		minutesAsString.insert(0, "0");
	}
	std::string secondsAsString = std::to_string(seconds);
	if (seconds < 10)
	{
		secondsAsString.insert(0, "0");
	}
	std::string currentTimeAsString =
		hoursAsString.append(":").append(minutesAsString).append(":").append(secondsAsString);
	// Render the current time in the digital clock's space, scale it 2/3 times and paint it white.
	timesNewRomanFont->renderText(*shaderProgramForNonlogoText, currentTimeAsString, 
		0.22625F * windowWidth, 0.81875F * windowHeight, 0.475F, glm::vec3(1.0F, 1.0F, 1.0F));

	std::string intensityOfBackgroundLightAsString = std::to_string(intensityOfBackgroundLight);
	intensityOfBackgroundLightAsString = intensityOfBackgroundLightAsString
		.substr(0U, intensityOfBackgroundLightAsString.size() - 4U);
	// Render the current intensity of the point light ("background light") in its widget's space, scale it
	// 2/3 times and paint it white.
	timesNewRomanFont->renderText(*shaderProgramForNonlogoText, intensityOfBackgroundLightAsString, 
		0.6275F * windowWidth, 0.653333F * windowHeight, 0.475F, glm::vec3(1.0F, 1.0F, 1.0F));

	std::string currentTemperatureOfFreezingChamberAsString = 
		std::to_string(currentTemperatureOfFreezingChamber);
	currentTemperatureOfFreezingChamberAsString = currentTemperatureOfFreezingChamberAsString
		.substr(0U, currentTemperatureOfFreezingChamberAsString.size() - 5U);
	// Render the current temperature of the freezing chamber in its widget's space, scale it 2/3 times and
	// paint it white.
	timesNewRomanFont->renderText(*shaderProgramForNonlogoText, currentTemperatureOfFreezingChamberAsString, 
		0.6125F * windowWidth, 0.816667F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));

	std::string currentTemperatureOfRefrigeratingChamberAsString = 
		std::to_string(currentTemperatureOfRefrigeratingChamber);
	currentTemperatureOfRefrigeratingChamberAsString = currentTemperatureOfRefrigeratingChamberAsString
		.substr(0U, currentTemperatureOfRefrigeratingChamberAsString.size() - 5U);
	// Render the current temperature of the refrigerating chamber in its widget's space, scale it 2/3 times and
	// paint it white.
	timesNewRomanFont->renderText(*shaderProgramForNonlogoText, currentTemperatureOfRefrigeratingChamberAsString, 
		0.63F * windowWidth, 0.718333F * windowHeight, 0.666667F, glm::vec3(1.0F, 1.0F, 1.0F));
}
