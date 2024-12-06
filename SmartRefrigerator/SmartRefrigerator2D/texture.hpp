// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// texture header. This prevents linking conflicts.
#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
	unsigned int id = 0U;
	int errorCode = 0;

	Texture(const char *imagePath)
	{
		// Tell the "stb_image.h" library to flip the y-axis during the image loading. This call is necessary because
		// OpenGL expects the 0.0f coordinate on the y-axis to be on the bottom side of the image, but images
		// usually have 0.0f at the top of the y-axis.
		stbi_set_flip_vertically_on_load(true);

		// Load the image that will be used as a texture.
		int textureImageWidth, textureImageHeight, numberOfColorChannelsInTextureImage;
		// int desiredNumberOfColorChannels = 4;
		unsigned char *pixels = stbi_load(imagePath, &textureImageWidth, &textureImageHeight, 
			&numberOfColorChannelsInTextureImage, 0);
		if (pixels == NULL)
		{
			std::cout << "Image of would-be-texture could not be loaded!" << std::endl;
			errorCode = 7;

			return;
		}
		// Determine the image format from the number of color channels in the texture image.
		GLenum format = 0U;
		switch (numberOfColorChannelsInTextureImage)
		{
		case 1:
			format = GL_RED;
			break;
		case 2:
			format = GL_RG;
			break;
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			stbi_image_free(pixels);
			errorCode = 8;

			return;
		}

		// Create memory on the GPU where the texture will be stored.
		glGenTextures(1, &id);
		// Bind (assign) the newly created texture to OpenGL's context.
		glBindTexture(GL_TEXTURE_2D, id);

		// Set the texture wrapping parameters. The texture coordinates are in range [0.0f, 1.0f]. If the texture
		// coordinates are specified outside of the mentioned range, the texture wrapping option determines the look.
		// Each texture wrapping option can be set per coordinate axis (s, t and r if 3D textures are used).
		// s-axis, t-axis and r-axis correspond to x-axis, y-axis and z-axis, respectively.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// Set the texture filtering parameters. The texture coordinates do not depend on the resolution, but can be any
		// floating point value. Therefore, OpenGL needs to figure out which texture pixel (texel) to map the
		// texture coordinate to. The nearest neighbour filtering is better suited for the minifying operations, while
		// the (bi)linear filtering is better suited for the magnifying operations.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// The mipmaps are used to improve the minifying, not the magnifying. Setting one of the mipmap filtering options
		// as the magnification filter will generate the OpenGL "GL_INVALID_ENUM" error code.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Generate a texture using the previously loaded image data (pixels).
		glTexImage2D(GL_TEXTURE_2D, 0, format, textureImageWidth, textureImageHeight, 0, format, 
			GL_UNSIGNED_BYTE, pixels);
		// Automatically generate all the required mipmaps for the currently bound texture.
		glGenerateMipmap(GL_TEXTURE_2D);

		// Free the image memory.
		stbi_image_free(pixels);

		// Unbind the texture for safety reasons.
		glBindTexture(GL_TEXTURE_2D, 0U);
	}

	// REFERENCE: https://www.geeksforgeeks.org/destructors-c/
	virtual ~Texture()
	{
		glDeleteTextures(1, &id);
	}
};
#endif
