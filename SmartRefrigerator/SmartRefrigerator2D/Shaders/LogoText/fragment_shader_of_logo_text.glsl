#version 330 core

in vec2 TexCoords;
in float OpacityFactorOfDistanceFromVerticalEdges;

out vec4 FragColor;

// Mono-colored bitmap image of the glyph.
uniform sampler2D text;
// Color uniform for adjusting the text's final color.
uniform vec3 colorOfText;

// Pressing the "2" key should start the color pulsing of the "LOK" company's logo.
uniform bool logoNeedsToPulse;
// Change the color of the "LOK" company's logo from blue to purple over time by changing the red component.
uniform float redColorComponentForPulsing;
// Pressing the "5" key should start the movement of the "LOK" company's logo from left to right and vice-versa between
// the window's edges. The closer the logo is to one of the edges, the more transparent it should be.
uniform bool logoNeedsToMoveLeftRightBetweenEdges;

void main()
{
	// Sampling the color value of the bitmap texture is the first step.
	// Because the texture's data is stored only in its red component, we sample that red component as the alpha value.
	// By varying the output color's alpha value, the resulting pixel will be transparent for all the glyph's background
	// colors and non-transparent for the actual character pixels. First three values of sampled color are set to 1.0F
	// to enable multiplication with the color of text the user chooses.
	vec4 sampledColor = vec4(1.0F, 1.0F, 1.0F, texture(text, TexCoords).r);
	// Finally, the samled RGB color is multiplied by the "colorOfText" uniform to get the resulting text color.
	FragColor = vec4(colorOfText, 1.0F) * sampledColor;

	if (logoNeedsToPulse)
	{
		FragColor.r = redColorComponentForPulsing;
	}
	if (logoNeedsToMoveLeftRightBetweenEdges)
	{
		if (FragColor.a > 0.0F)
		{
			FragColor.a -= OpacityFactorOfDistanceFromVerticalEdges;
			if (FragColor.a <= 0.0F)
			{
				FragColor.a = 0.1F;
			}
			if (FragColor.a > 1.0F)
			{
				FragColor.a = 1.0F;
			}
		}
	}
}
