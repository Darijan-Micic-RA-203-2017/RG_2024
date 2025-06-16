// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// chamber rendering header. This prevents linking conflicts.
#ifndef CHAMBER_RENDERING_H
#define CHAMBER_RENDERING_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "global_variables.hpp"

void renderChamber();

#endif
