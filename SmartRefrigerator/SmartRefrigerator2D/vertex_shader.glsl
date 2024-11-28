#version 330 core

layout (location = 0U) in vec2 aPos;
layout (location = 1U) in vec4 aColor;
layout (location = 2U) in vec2 aTexCoords;

out vec4 Color;
out vec2 TexCoords;

void main()
{
	Color = aColor;
	TexCoords = aTexCoords;

	gl_Position = vec4(aPos, 0.0F, 1.0F);
}
