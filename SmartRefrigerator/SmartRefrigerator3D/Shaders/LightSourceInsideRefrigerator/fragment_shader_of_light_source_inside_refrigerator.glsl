#version 330 core

out vec4 FragColor;

uniform float currentAvgTemperatureOfRefrigerator;

void main()
{
	const float minAvgTemperatureOfRefrigerator = -20.0F;
	const float maxAvgTemperatureOfRefrigerator = -5.5F;

	float blueColorComponentOfLight = (currentAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator) / 
		(maxAvgTemperatureOfRefrigerator - minAvgTemperatureOfRefrigerator);
	// Set the light source inside refrigerator to emit some nuance of yellow-colored light.
	// When the average temperature of the refrigerator is at its minimum (-20.0F), the light will be fully yellow.
	// When the average temperature of the refrigerator is at its maximum (-5.5F), the light will be fully white.
	FragColor = vec4(vec3(1.0F, 1.0F, blueColorComponentOfLight), 1.0F);
}
