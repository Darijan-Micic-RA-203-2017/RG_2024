#version 330 core

in vec4 Color;

out vec4 FragColor;

uniform float intensityOfBackgroundLight;

void main()
{
	FragColor = intensityOfBackgroundLight * Color;
}
