// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// nonlogo signature text rendering header. This prevents linking conflicts.
#ifndef NONLOGO_SIGNATURE_TEXT_RENDERING_H
#define NONLOGO_SIGNATURE_TEXT_RENDERING_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "global_variables.hpp"

void renderNonlogoSignatureText();

#endif
