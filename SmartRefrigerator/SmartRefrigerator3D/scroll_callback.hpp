// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// scroll callback header. This prevents linking conflicts.
#ifndef SCROLL_CALLBACK_H
#define SCROLL_CALLBACK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global_variables.hpp"

// Function that will be called every time the user scrolls the mouse's middle button.
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif
