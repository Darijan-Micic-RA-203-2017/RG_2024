#version 330 core

layout (location = 0U) in vec3 aPos;
layout (location = 1U) in vec3 aNormal;
layout (location = 2U) in vec2 aTexCoords;

out vec2 TexCoords;

// Pass the transformational matrices to the vertex shader.
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	TexCoords = aTexCoords;

	// Vclip = Mprojection * Mview * Mmodel * Vlocal. The multiplication of matrices is meant to be read from right.
	// OpenGL will automatically perform the perspective division and clipping after it is provided with the output
	// variable "gl_Position". The output variable "gl_Position" represents the clip-space coordinates.
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0F);
}
