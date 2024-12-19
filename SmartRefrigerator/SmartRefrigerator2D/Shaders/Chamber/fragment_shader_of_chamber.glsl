#version 330 core

in vec4 Color;

out vec4 FragColor;

uniform bool seeThroughModeTurnedOn;
uniform float windowWidth;
uniform float windowHeight;
uniform float currentTemperatureOfFreezingChamber;
uniform float currentTemperatureOfRefrigeratingChamber;

void main()
{
	vec4 resultingColorOfFragment = Color;
	if (!seeThroughModeTurnedOn)
	{
		FragColor = resultingColorOfFragment;

		return;
	}
	
	const float minTemperatureOfFreezingChamber = -40.0F;
	const float maxTemperatureOfFreezingChamber = -18.0F;
	const float minTemperatureOfRefrigeratingChamber = 0.0F;
	const float maxTemperatureOfRefrigeratingChamber = 7.0F;

	// The built-in "gl_FragCoord" vector variable has its x-value and y-value in screen-space coordinates.
	// Because of that, the normalized device coordinates (NDCs) used to describe the vertex's position in the main
	// program have to be converted to the [0.0F, 1.0F] range and multiplied with window's width/height. Only then can
	// the single values of the "gl_FragCoord" vector be compared with the borders of the chambers.
	if (gl_FragCoord.x >= 0.25F * windowWidth && gl_FragCoord.x <= 0.75F * windowWidth)
	{
		if (gl_FragCoord.y >= 0.38F * windowHeight && gl_FragCoord.y <= 0.62F * windowHeight)
		{
			// minFreezChmbT <= currFreezChmbT <= maxFreezChmbT / + (-left_side)
			// 0.0F <= currFreezChmbT - minFreezChmbT <= maxFreezChmbT - minFreezChmbT / : right_side
			// 0.0F <= (currFreezChmbT - minFreezChmbT) / (maxFreezChmbT - minFreezChmbT) <= 1.0F
			// resultingColorOfFragment.a = (1.0F - the_expression_in_the_middle) / 2.0F.
			resultingColorOfFragment.a = (1.0F - 
				(currentTemperatureOfFreezingChamber - minTemperatureOfFreezingChamber) / 
					(maxTemperatureOfFreezingChamber - minTemperatureOfFreezingChamber)) / 2.0F;
		}
		else if (gl_FragCoord.y >= 0.13F * windowHeight && gl_FragCoord.y <= 0.37F * windowHeight)
		{
			// minRefrigChmbT <= currRefrigChmbT <= maxRefrigChmbT / + (-left_side)
			// 0.0F <= currRefrigChmbT - minRefrigChmbT <= maxRefrigChmbT - minRefrigChmbT / : right_side
			// 0.0F <= (currRefrigChmbT - minRefrigChmbT) / (maxRefrigChmbT - minRefrigChmbT) <= 1.0F
			// resultingColorOfFragment.a = (1.0F - the_expression_in_the_middle) / 2.0F.
			resultingColorOfFragment.a = (1.0F - 
				(currentTemperatureOfRefrigeratingChamber - minTemperatureOfRefrigeratingChamber) / 
					(maxTemperatureOfRefrigeratingChamber - minTemperatureOfRefrigeratingChamber)) / 2.0F;
		}
	}
	FragColor = resultingColorOfFragment;
}
