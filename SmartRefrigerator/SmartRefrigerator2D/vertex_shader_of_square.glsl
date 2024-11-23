#version 330 core

layout (location = 0U) in vec2 aPos;
layout (location = 1U) in vec3 aColor;

out vec3 Color;

void main()
{
	Color = aColor;

	gl_Position = vec4(aPos, 0.0F, 1.0F);
}
