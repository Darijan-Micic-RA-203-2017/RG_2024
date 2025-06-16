// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// rendering header. This prevents linking conflicts.
#ifndef RENDERING_H
#define RENDERING_H

#include "grocery_rendering.hpp"
#include "chamber_rendering.hpp"
#include "refrigerator_rendering.hpp"
#include "refrigerator_door_rendering.hpp"
#include "light_source_inside_refrigerator_rendering.hpp"
#include "nonlogo_readings_text_rendering.hpp"

#endif
