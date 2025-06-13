#include "graphical_mode_variables.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The graphical mode is the initial mode of the application. It also starts after the user clicks anywhere on the
// screen during the logo mode. Graphic mode consists of showing the temperature widgets for the freezing and the
// refrigerating chamber and the digital clock.
bool graphicalModeTurnedOn = true;
float timeWhenGraphicalModeWasActivated = 0.0F;
GLenum polygonMode = GL_FILL;
bool sceneLit = true;
// When the orthogonal projection is turned on, this 3D project acts as the 2D project and the mouse cursor is visible.
// Otherwise, the entire refrigerator can be seen and the mouse cursor is hidden.
bool orthogonalProjectionTurnedOn = true;
bool groceryInsideFreezer = false;

// This factor affects not only the intensity of background, but all elements of graphic display.
float intensityOfBackgroundLight = 1.0F;

// The see-through mode starts after the user clicks on that mode activation button during the graphical mode.
// See-through mode consists of showing the groceries inside the smart refrigerator.
float seeThroughModeTurnedOn = false;

// If the user clicks on the door handle, it should open.
bool doorOpen = false;
