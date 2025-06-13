// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// input processing header. This prevents linking conflicts.
#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include "global_variables.hpp"

// Input processing function.
void processInput(GLFWwindow *window);

#endif
