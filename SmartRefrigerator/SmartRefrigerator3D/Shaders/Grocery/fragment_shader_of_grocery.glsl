#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D fishSticksPackage;
uniform sampler2D milkCartonBox;
uniform bool groceryInsideFreezer;

void main()
{
	vec4 resultingColorOfFragment = vec4(0.0F);
	if (groceryInsideFreezer)
	{
		resultingColorOfFragment = texture(fishSticksPackage, TexCoords);
	}
	else
	{
		resultingColorOfFragment = texture(milkCartonBox, TexCoords);
	}

	if (resultingColorOfFragment.a < 0.1F)
	{
		discard;
	}
	FragColor = resultingColorOfFragment;
}
