// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// nonlogo readings text rendering header. This prevents linking conflicts.
#ifndef NONLOGO_READINGS_TEXT_RENDERING_H
#define NONLOGO_READINGS_TEXT_RENDERING_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// REFERENCE: https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/localtime-s-localtime32-s-localtime64-s?view=msvc-170
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "global_variables.hpp"

void renderNonlogoReadingsText();

#endif
