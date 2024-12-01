#version 330 core

layout (location = 0U) in vec2 aPos;
layout (location = 1U) in vec4 aColor;

out vec4 Color;

void main()
{
	Color = aColor;

	gl_Position = vec4(aPos, 0.0F, 1.0F);
}
