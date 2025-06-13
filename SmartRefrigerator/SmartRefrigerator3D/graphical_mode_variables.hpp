// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// graphical mode variables header. This prevents linking conflicts.
#ifndef GRAPHICAL_MODE_VARIABLES_H
#define GRAPHICAL_MODE_VARIABLES_H

#include <GL/glew.h>
#include "door_state.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The graphical mode is the initial mode of the application. It also starts after the user clicks anywhere on the
// screen during the logo mode. Graphic mode consists of showing the temperature widgets for the freezing and the
// refrigerating chamber and the digital clock.
extern bool graphicalModeTurnedOn;
extern float timeWhenGraphicalModeWasActivated;
extern GLenum polygonMode;
extern bool sceneLit;
// When the orthogonal projection is turned on, this 3D project acts as the 2D project and the mouse cursor is visible.
// Otherwise, the entire refrigerator can be seen and the mouse cursor is hidden.
extern bool orthogonalProjectionTurnedOn;
extern bool groceryInsideFreezer;

// This factor affects not only the intensity of background, but all elements of graphic display.
extern float intensityOfBackgroundLight;

// The see-through mode starts after the user clicks on that mode activation button during the graphical mode.
// See-through mode consists of showing the groceries inside the smart refrigerator.
extern float seeThroughModeTurnedOn;

// If the user clicks on the door handle, it should open.
extern DoorState doorState;

#endif
