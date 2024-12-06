#version 330 core

in vec4 Color;

out vec4 FragColor;

uniform bool seeThroughModeTurnedOn;
uniform float currentTemperatureOfFreezingChamber;
uniform float currentTemperatureOfRefrigeratingChamber;

void main()
{
	FragColor = Color;
	if (!seeThroughModeTurnedOn)
	{
		return;
	}
	
	const float minTemperatureOfFreezingChamber = -40.0F;
	const float maxTemperatureOfFreezingChamber = -18.0F;
	const float minTemperatureOfRefrigeratingChamber = 0.0F;
	const float maxTemperatureOfRefrigeratingChamber = 7.0F;

	if (gl_FragCoord.x >= -0.5F && gl_FragCoord.x <= 0.5F)
	{
		if (gl_FragCoord.y >= -0.24F && gl_FragCoord.y <= 0.24F)
		{
			FragColor.a = clamp(maxTemperatureOfFreezingChamber - currentTemperatureOfFreezingChamber, 0.0F, 0.5F);
		}
		else if (gl_FragCoord.y >= -0.74F && gl_FragCoord.y <= -0.26F)
		{
			FragColor.a = 
				clamp(maxTemperatureOfRefrigeratingChamber - currentTemperatureOfRefrigeratingChamber, 0.0F, 0.5F);
		}
	}
}
