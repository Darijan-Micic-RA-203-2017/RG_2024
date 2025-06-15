// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// array and buffer objects header. This prevents linking conflicts.
#ifndef ARRAY_AND_BUFFER_OBJECTS_H
#define ARRAY_AND_BUFFER_OBJECTS_H

#include <GL/glew.h>
#include "vertices.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

extern unsigned int groceriesVAO;
extern unsigned int chambersVAO;
extern unsigned int refrigeratorVAO;
extern unsigned int refrigeratorDoorsVAO;
extern unsigned int lightSourceInsideRefrigeratorVAO;
extern unsigned int textVAO;
extern unsigned int groceriesVBO;
extern unsigned int chambersVBO;
extern unsigned int refrigeratorVBO;
extern unsigned int refrigeratorDoorsVBO;
extern unsigned int lightSourceInsideRefrigeratorVBO;
extern unsigned int textVBO;

void generateArrayAndBufferObjects();
void copyUserDefinedDataToGPUAndTellOpenGLHowItShouldInterpretIt();
void unbindArrayAndBufferObjectsForSafetyReasons();
void setUpArrayAndBufferObjects();

#endif
