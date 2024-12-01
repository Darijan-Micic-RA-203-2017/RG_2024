// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// text header. This prevents linking conflicts.
#ifndef TEXT_H
#define TEXT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <iostream>
#include <map>
#include <string>
#include "shader_program.hpp"

class Text
{
private:
	// Generate the texture for the loaded character glyph.
	unsigned int generateTextureForLoadedGlyph(FT_Face& face)
	{
		unsigned int textureID;
		// Create memory on the GPU where the texture will be stored.
		glGenTextures(1, &textureID);
		// Bind (assign) the newly created texture to OpenGL's context.
		glBindTexture(GL_TEXTURE_2D, textureID);

		// Set the texture wrapping parameters. The texture coordinates are in range [0.0f, 1.0f]. If the texture
		// coordinates are specified outside of the mentioned range, the texture wrapping option determines the look.
		// Each texture wrapping option can be set per coordinate axis (s, t and r if 3D textures are used).
		// s-axis, t-axis and r-axis correspond to x-axis, y-axis and z-axis, respectively.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// Set the texture filtering parameters. The texture coordinates do not depend on the resolution, but can be any
		// floating point value. Therefore, OpenGL needs to figure out which texture pixel (texel) to map the texture
		// coordinate to. The nearest neighbour filtering is better suited for the minifying operations, while the
		// (bi)linear filtering is better suited for the magnifying operations.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Generate a texture using the previously created 8-bit grayscale bitmap image.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
			GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		// The bitmap generated from the glyph is a grayscale 8-bit image, where each color is represented by a single
		// byte. For this reason, it is needed to store each byte of the bitmap buffer as the texture's single color
		// value. This is accomplished by creating a texture where each byte corresponds to the texture color's red
		// component (first byte of its color vector).

		return textureID;
	}

	// Store the character for later use.
	void storeCharacter(unsigned char c, unsigned int textureID, FT_Face face)
	{
		Character character = {
			textureID,
			// Width and height of the bitmap (in pixels).
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			// Horizontal position ("bearingX") of the bitmap relative to the origin (in pixels).
			// Vertical position ("bearingY") of the bitmap relative to the baseline (in pixels).
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			// Horizontal distance ("advance") from the origin to the origin of the next glyph (in 1/64th pixels).
			static_cast<unsigned int>(face->glyph->advance.x)
		};
		characters.insert(std::pair<char, Character>(c, character));
	}

	void extractNecessaryInfoFromFaceOn(std::string pathOfFace)
	{
		// Initialize the FreeType library.
		// All functions of this library return a value different than 0 whenever an error occurres.
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "FreeType library was not initialized!" << std::endl;
			FT_Done_FreeType(ft);
			errorCode = 9;

			return;
		}

		// Load the font or, as the FreeType library calls it, the face.
		// A TrueType font is a collection of character glyphs not defined by pixels or any other non-scalable solution,
		// but by mathematical equations (combinations of splines). Similar to vector images, the rasterized font images
		// can be procedurally generated based on the preferred font height the user would like to obtain them in.
		// Using TrueType fonts enables easy rendering of character glyphs of various sizes without any loss of quality.
		FT_Face face;
		if (FT_New_Face(ft, pathOfFace.c_str(), 0L, &face))
		{
			std::cout << "Font was not loaded!" << std::endl;
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
			errorCode = 10;

			return;
		}

		// Specify the size of glyphs (the pixel font size to be extracted from the face).
		// Setting the width to 0U tells the face (font) to dynamically calculate the width based on the given height.
		FT_Set_Pixel_Sizes(face, 0U, 48U);

		// Disable the byte-alignment restriction. If a single byte is used to represent each of the colors of a
		// texture, one restriction of OpenGL needs to be taken care of. OpenGL requires that textures all have a 4-byte
		// alignment, e.g. their size is always a multiple of 4 bytes. Normally, this won't be a problem since most
		// textures have a width that is a multiple of 4 and/or use 4 bytes per pixel. However, if only a single byte is
		// used per pixel, the texture can have any possible width. Its unpack alignment must be set to 1 to ensure
		// there are no alignment issues, which could cause segmentation faults.
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// Load the first 128 characters of the ASCII set.
		for (unsigned char c = 0U; c < 128U; c++)
		{
			// Load the character glyph.
			// A FreeType face hosts a collection of glyphs. One of those glyphs can be set as the active glyph by
			// calling the "FT_Load_Char" method. By setting "FT_LOAD_RENDER" as one of the loading flags, FreeType
			// library is told to create an 8-bit grayscale bitmap image. That image can be accessed in this way: face->glyph->bitmap.
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "Glyph was not loaded!" << std::endl;

				continue;
			}

			unsigned int texture = generateTextureForLoadedGlyph(face);
			storeCharacter(c, texture, face);
		}

		// Unbind the texture before the next loop iteration.
		glBindTexture(GL_TEXTURE_2D, 0U);

		// Destroy the loaded font (face), thus freeing all its allocated memory.
		FT_Done_Face(face);
		// Terminate the FreeType library.
		FT_Done_FreeType(ft);
	}
public:
	std::string pathOfFace;
	// Holds all state information relevant to a character as loaded using the FreeType library.
	// It is possible to load a character glyph, retrieve its metrics and generate a texture each time a character needs
	// to be rendered to the screen, but it would be inefficient to do this each frame. It is smarter to store the
	// generated data somewhere in the application and query it whenever a character needs to be rendered. This
	// convenient structure serves that purpose. It is then stored in a map.
	struct Character {
		// Id of the glyph texture.
		unsigned int textureID;
		// Size of the glyph, a.k.a. its width and height.
		glm::ivec2 size;
		// Offset from the baseline to left/top of glyph.
		glm::ivec2 bearing;
		// Horizontal offset to advance to next glyph.
		unsigned int advance;
	};
	// Map of all necessary characters, with character's code serving as the key.
	std::map<GLchar, Character> characters;
	// VAO and VBO used to store the text and text's info, provided in constructor.
	unsigned int VAO = 0U;
	unsigned int VBO = 0U;
	int errorCode = 0;

	Text(std::string pathOfFace, unsigned int VAO, unsigned int VBO)
	{
		this->pathOfFace = pathOfFace;
		this->VAO = VAO;
		this->VBO = VBO;

		extractNecessaryInfoFromFaceOn(pathOfFace);
	}

	// Renders text, with position (x, y) being the encompassing text quad's bottom left corner.
	void renderText(ShaderProgram& shaderProgram, std::string text, float x, float y, float scale, glm::vec3 color)
	{
		// Activate the corresponding render state.
		shaderProgram.useProgram();
		shaderProgram.setFloatVec3Uniform("colorOfText", color.x, color.y, color.z);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(VAO);

		// Calculate the dimensions of each quad based on the corresponding character's metrics.
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = characters[*c];

			float xPos = x + ch.bearing.x * scale;
			// Some characters (like 'p' or 'g') are rendered slightly below the baseline, so the quad should also be
			// positioned slightly below RenderText's y value. The exact amount "yPos" needs to be offseted below the
			// baseline can be figured out from the glyph metrics. The distance a glyph extends below the baseline is
			// necessary for calculating this distance (offset). The length of this vector can be calculated by
			// subtracting "bearingY" from the glyph's (bitmap's) height. This value is then 0.0F for characters that
			// rest on the baseline (like 'X') and positive for characters that reside slightly below the baseline
			// (like 'g' or 'j').
			float yPos = y - (ch.size.y - ch.bearing.y) * scale;

			float width = ch.size.x * scale;
			float height = ch.size.y * scale;
			// Update the VBO for each character. Multidimensional vertices array has 6 rows because it takes 6 vertices
			// to draw a rectangle and 4 columns because each vertex contains position (2 coordinates - x and y) and
			// texture coordiantes (2 coordiantes - s and t).
			float vertices[6][4] = {
				{ xPos,         yPos + height, 0.0F, 0.0F },
				{ xPos,         yPos,          0.0F, 1.0F },
				{ xPos + width, yPos,          1.0F, 1.0F },

				{ xPos,         yPos + height, 0.0F, 0.0F },
				{ xPos + width, yPos,          1.0F, 1.0F },
				{ xPos + width, yPos + height, 1.0F, 0.0F }
			};
			// Render the glyph texture over the quad.
			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			// Update the content of the VBO memory.
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			// Unbind the VBO for safety reasons.
			glBindBuffer(GL_ARRAY_BUFFER, 0U);

			// Render the quad as two triangles.
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance the cursors for the next glyph. REMEMBER THAT THE ADVANCE IS MEASURED IN 1/64TH PIXELS!
			x += (ch.advance >> 6U) * scale;
			// Bitshift to the left by 6 to get value in pixels (2^6 = 64).
		}

		// Unbind the VAO and the texture for safety reasons.
		glBindVertexArray(0U);
		glBindTexture(GL_TEXTURE_2D, 0U);
	}
};
#endif
