// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// cursors and their variables header. This prevents linking conflicts.
#ifndef CURSORS_AND_THEIR_VARIABLES_H
#define CURSORS_AND_THEIR_VARIABLES_H

#include <GLFW/glfw3.h>
#include "window_dimensions.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The cursor that will be shown when the mouse is hovering over the freezing chamber in the orthogonal projection mode.
extern GLFWcursor *blueSnowflakeCursor;
// Is this the first time the mouse entry is captured?
extern bool firstMouseEntry;
// Previous cursor position is initialized to the half of the window's size.
extern float previousCursorPosX;
extern float previousCursorPosY;

#endif
