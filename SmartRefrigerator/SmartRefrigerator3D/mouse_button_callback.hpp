// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// mouse button callback header. This prevents linking conflicts.
#ifndef MOUSE_BUTTON_CALLBACK_H
#define MOUSE_BUTTON_CALLBACK_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "global_variables.hpp"

// Function that processes clicking on mouse buttons.
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

#endif
