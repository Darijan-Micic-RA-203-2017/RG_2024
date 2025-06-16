// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// logo text rendering header. This prevents linking conflicts.
#ifndef LOGO_TEXT_RENDERING_H
#define LOGO_TEXT_RENDERING_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "global_variables.hpp"

void renderLogoText();

#endif
