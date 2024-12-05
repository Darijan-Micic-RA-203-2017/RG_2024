#version 330 core

// <vec2 pos, vec2 texCoords>
layout (location = 0U) in vec4 vertex;

out vec2 TexCoords;

// Text rendering usually does not require the use of the perspective projection. Therefore, an ortographic projection
// matrix will suffice. Using an orthographic projection matrix also allows all vertex coordinates to be specified in
// screen-space coordinates. In order to take advantage of this, the projection matrix needs to be set up this way:
// glm::mat4 projectionMatrix = glm::ortho(0.0F, windowWidth, 0.0F, windowHeight).
// The projection matrix's bottom parameter is set to 0.0F and its top parameter equal to the window's height.
// The result is that coordinates can be specified with y-values ranging from the bottom part of the screen (0.0F) to
// the top part of the screen (window's height). The point (0.0F, 0.0F) now corresponds to the bottom-left corner.
uniform mat4 projectionMatrix;

void main()
{
	TexCoords = vertex.zw;

	gl_Position = projectionMatrix * vec4(vertex.xy, 0.0F, 1.0F);
}
