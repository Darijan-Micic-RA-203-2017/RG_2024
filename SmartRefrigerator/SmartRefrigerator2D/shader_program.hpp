// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// shader program header. This prevents linking conflicts.
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class ShaderProgram
{
private:
	// Utility function for checking whether the compilation of shader or linking of shader program succeeded.
	// Function prints out the error if it did not.
	void checkForCompilationOrLinkingErrors(unsigned int shaderOrProgram, std::string type)
	{
		int success;
		char infoLog[512U];
		if (type != "Shader program")
		{
			glGetShaderiv(shaderOrProgram, GL_COMPILE_STATUS, &success);
			if (success == 0)
			{
				glGetShaderInfoLog(shaderOrProgram, 512, NULL, infoLog);
				std::cout << type << " was not compiled!\n" << infoLog << std::endl;
				if (type == "Vertex shader")
				{
					errorCode = 4;
				}
				else
				{
					errorCode = 5;
				}

				return;
			}
		}
		else
		{
			glGetProgramiv(shaderOrProgram, GL_LINK_STATUS, &success);
			if (success == 0)
			{
				glGetProgramInfoLog(shaderOrProgram, 512, NULL, infoLog);
				std::cout << type << " was not linked!\n" << infoLog << std::endl;
				errorCode = 6;

				return;
			}
		}

		errorCode = 0;
	}
public:
	unsigned int id = 0U;
	int errorCode = 0;

	ShaderProgram(const char *vertexShaderSourcePath, const char *fragmentShaderSourcePath)
	{
		// Retrieve the source code of shaders from the files on paths provided as the parameters of this function.
		std::string sourceCodeOfVS;
		std::string sourceCodeOfFS;
		std::ifstream fileWithSourceCodeOfVertexShader;
		std::ifstream fileWithSourceCodeOfFragmentShader;

		// Ensure that the input file stream objects can throw exceptions.
		fileWithSourceCodeOfVertexShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fileWithSourceCodeOfFragmentShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);

		try
		{
			// Open the files containing the source codes of shaders.
			fileWithSourceCodeOfVertexShader.open(vertexShaderSourcePath);
			fileWithSourceCodeOfFragmentShader.open(fragmentShaderSourcePath);

			// Read the buffer contents of files into streams.
			std::stringstream vertexShaderStream;
			std::stringstream fragmentShaderStream;
			vertexShaderStream << fileWithSourceCodeOfVertexShader.rdbuf();
			fragmentShaderStream << fileWithSourceCodeOfFragmentShader.rdbuf();

			// Close the file handlers.
			fileWithSourceCodeOfVertexShader.close();
			fileWithSourceCodeOfFragmentShader.close();

			// Convert the stream into a string.
			sourceCodeOfVS = vertexShaderStream.str();
			sourceCodeOfFS = fragmentShaderStream.str();
		}
		catch (std::ifstream::failure &e)
		{
			std::cout << "File containing the source code of shader was not successfully read!\n" << e.what() << std::endl;

			return;
		}

		// Get the constant pointer to the first character of the underlying null-terminated string.
		const char *sourceCodeOfVertexShader = sourceCodeOfVS.c_str();
		const char *sourceCodeOfFragmentShader = sourceCodeOfFS.c_str();

		// Create the vertex shader object.
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// Attach the source code of the vertex shader to its object.
		glShaderSource(vertexShader, 1, &sourceCodeOfVertexShader, NULL);
		// Dynamically compile the vertex shader at run-time.
		glCompileShader(vertexShader);
		// Check whether the compilation of vertex shader succeeded and print out the error if it did not.
		checkForCompilationOrLinkingErrors(vertexShader, "Vertex shader");
		if (errorCode == 4)
		{
			glDeleteShader(vertexShader);

			return;
		}

		// Create the fragment shader object.
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		// Attach the source code of the fragment shader to its object.
		glShaderSource(fragmentShader, 1, &sourceCodeOfFragmentShader, NULL);
		// Dynamically compile the fragment shader at run-time.
		glCompileShader(fragmentShader);
		// Check whether the compilation of fragment shader succeeded and print out the error if it did not.
		checkForCompilationOrLinkingErrors(fragmentShader, "Fragment shader");
		if (errorCode == 5)
		{
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		// Create the shader program object.
		id = glCreateProgram();
		// Attach the previously compiled shaders to the shader program.
		glAttachShader(id, vertexShader);
		glAttachShader(id, fragmentShader);
		// Link previously compiled shaders into a program.
		// The outputs of each shader are linked to the inputs of next shader.
		glLinkProgram(id);
		// Check whether the linking of shader program succeeded and print out the error if it did not.
		checkForCompilationOrLinkingErrors(id, "Shader program");
		if (errorCode == 6)
		{
			glDeleteProgram(id);
		}

		// Delete shader objects after linking, they are no longer needed.
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
	}

	// Utility function for using (activating) the shader program.
	void useProgram()
	{
		glUseProgram(id);
	}

	// Utility functions for updating the various types of uniform variables.
	void setBoolUniform(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int) value);
	}

	void setUnsignedIntegerUniform(const std::string &name, unsigned int value) const
	{
		glUniform1ui(glGetUniformLocation(id, name.c_str()), value);
	}

	void setIntegerUniform(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}

	void setFloatUniform(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}

	void setFloatVec2Uniform(const std::string &name, float value0, float value1) const
	{
		glUniform2f(glGetUniformLocation(id, name.c_str()), value0, value1);
	}

	void setFloatVec3Uniform(const std::string &name, float value0, float value1, float value2) const
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), value0, value1, value2);
	}

	void setFloatVec4Uniform(const std::string &name, float value0, float value1, float value2, float value3) const
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), value0, value1, value2, value3);
	}
};
#endif
