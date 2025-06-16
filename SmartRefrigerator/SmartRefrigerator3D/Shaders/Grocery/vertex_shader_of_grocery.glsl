#version 330 core

layout (location = 0U) in vec3 aPos;
layout (location = 1U) in vec3 aNormal;
layout (location = 2U) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

// Pass the normal matrix to the vertex shader.
uniform mat3 normalMatrix;
// Pass the transformational matrices to the vertex shader.
uniform mat4 modelMatrix;
// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
layout (std140) uniform ViewAndProjectionMatrices
{
	mat4 viewMatrix;
	mat4 projectionMatrix;
};

void main()
{
	// All lighting calculations will be done in the world space, so the fragment's position needs to be in world-space
	// coordinates. Converting the vertex's position to world-space coordinates is done by multiplying it with the model
	// matrix only.
	// Constructor that takes a parameter of type "vec4" of class "vec3" discards the last row.
	FragPos = vec3(modelMatrix * vec4(aPos, 1.0F));
	// The normal vector is multiplied with the normal matrix to ensure that normal vector is still perpendicular to
	// the vertex's surface. In other words, all transformations in the model matrix are undone.
	Normal = normalMatrix * aNormal;
	TexCoords = aTexCoords;

	// Vclip = Mprojection * Mview * Mmodel * Vlocal. The multiplication of matrices is meant to be read from right.
	// OpenGL will automatically perform the perspective division and clipping after it is provided with the output
	// variable "gl_Position". The output variable "gl_Position" represents the clip-space coordinates.
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0F);
}
