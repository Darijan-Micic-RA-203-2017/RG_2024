// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// framebuffer size callback header. This prevents linking conflicts.
#ifndef FRAMEBUFFER_SIZE_CALLBACK_H
#define FRAMEBUFFER_SIZE_CALLBACK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global_variables.hpp"

// Function that will be called every time the application's window changes size.
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif
