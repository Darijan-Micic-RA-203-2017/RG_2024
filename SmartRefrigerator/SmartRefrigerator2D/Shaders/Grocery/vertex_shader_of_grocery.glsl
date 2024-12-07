#version 330 core

layout (location = 0U) in vec2 aPos;
layout (location = 1U) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
	TexCoords = aTexCoords;

	gl_Position = vec4(aPos, 0.0F, 1.0F);
}
