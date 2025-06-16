// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// cursor position callback header. This prevents linking conflicts.
#ifndef CURSOR_POS_CALLBACK_H
#define CURSOR_POS_CALLBACK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global_variables.hpp"

// Function that will be called every time the user moves the mouse while the application has focus.
void cursor_pos_callback(GLFWwindow *window, double xpos, double ypos);

#endif
