// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// shader programs header. This prevents linking conflicts.
#ifndef SHADER_PROGRAMS_H
#define SHADER_PROGRAMS_H

#include "shader_program.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here
extern ShaderProgram *shaderProgramForGrocery;
extern ShaderProgram *shaderProgramForChamber;
extern ShaderProgram *shaderProgramForRefrigerator;
extern ShaderProgram *shaderProgramForLightSourceInsideRefrigerator;
extern ShaderProgram *shaderProgramForNonlogoText;
extern ShaderProgram *shaderProgramForLogoText;

int compileShadersAndLinkShaderPrograms();

#endif
