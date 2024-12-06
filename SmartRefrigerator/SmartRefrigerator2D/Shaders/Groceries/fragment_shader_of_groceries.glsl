#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D fishSticksPackage;
uniform sampler2D milkCartonBox;
uniform bool groceryInsideFreezer;

void main()
{
	if (groceryInsideFreezer)
	{
		FragColor = texture(fishSticksPackage, TexCoords);
	}
	else
	{
		FragColor = texture(milkCartonBox, TexCoords);
	}
}
