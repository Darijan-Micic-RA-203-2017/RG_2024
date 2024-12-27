#version 330 core

in vec2 TexCoords;

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
// Send the window width. Half of it is the screen space center's x-coodinate.
uniform float windowWidth;

void main()
{
	// Sampling the color value of the bitmap texture is the first step.
	// Because the texture's data is stored only in its red component, we sample that red component as the alpha value.
	// By varying the output color's alpha value, the resulting pixel will be transparent for all the glyph's background
	// colors and non-transparent for the actual character pixels. First three values of sampled color are set to 1.0F
	// to enable multiplication with the color of text the user chooses.
	vec4 sampledColor = vec4(1.0F, 1.0F, 1.0F, texture(text, TexCoords).r);
	// Finally, the samled RGB color is multiplied by the "colorOfText" uniform to get the resulting text color.
	vec4 resultingColorOfFragment = vec4(colorOfText, 1.0F) * sampledColor;

	if (logoNeedsToPulse)
	{
		resultingColorOfFragment.r = redColorComponentForPulsing;
	}
	if (logoNeedsToMoveLeftRightBetweenEdges)
	{
		float centerXOfScreenSpace = windowWidth / 2.0F;
		float difference = centerXOfScreenSpace - gl_FragCoord.x;
		float alphaFactor = abs(difference) / centerXOfScreenSpace;
		if (difference == centerXOfScreenSpace || difference == 0.0F)
		{
			alphaFactor = 0.0F;
		}
		else if (difference >= 0.0F)
		{
			alphaFactor -= 0.5F;
		}
		resultingColorOfFragment.a *= alphaFactor;
	}
	FragColor = resultingColorOfFragment;
}
