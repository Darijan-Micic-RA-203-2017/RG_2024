#version 330 core

in vec4 Color;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture0;

void main()
{
	FragColor = vec4(texture2D(texture0, TexCoords));
}
