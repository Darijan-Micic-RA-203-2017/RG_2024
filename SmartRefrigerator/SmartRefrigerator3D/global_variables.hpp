// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// global variables header. This prevents linking conflicts.
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "temperature_variables.hpp"
#include "graphical_mode_variables.hpp"
#include "logo_mode_variables.hpp"
#include "frame_rate_variables.hpp"
#include "cursors_and_their_variables.hpp"
#include "shader_programs.hpp"
#include "array_and_buffer_objects.hpp"
#include "textures.hpp"
#include "fonts.hpp"
#include "camera.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

extern glm::mat4 modelMatrix;
extern glm::mat4 viewMatrix;
extern glm::mat4 projectionMatrix;
extern glm::mat4 normalMatrix;
// All settings are kept in an instance of the camera class.
extern Camera *camera;

#endif
