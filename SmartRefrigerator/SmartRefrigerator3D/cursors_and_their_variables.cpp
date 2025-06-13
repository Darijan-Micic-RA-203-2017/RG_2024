#include "cursors_and_their_variables.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The cursor that will be shown when the mouse is hovering over the freezing chamber in the orthogonal projection mode.
GLFWcursor *blueSnowflakeCursor = NULL;
// Is this the first time the mouse entry is captured?
bool firstMouseEntry = true;
// Previous cursor position is initialized to the half of the window's size.
float previousCursorPosX = static_cast<float>(windowWidth) / 2.0F;
float previousCursorPosY = static_cast<float>(windowHeight) / 2.0F;
