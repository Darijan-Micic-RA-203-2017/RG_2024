// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// logo mode variables header. This prevents linking conflicts.
#ifndef LOGO_MODE_VARIABLES_H
#define LOGO_MODE_VARIABLES_H

#include "window_dimensions.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The logo mode starts 5 seconds after the user last clicked on the refrigerator's graphic display and ends when the
// user clicks on it again. Logo mode consists of showing the "LOK" company logo over the screen.
extern bool logoModeTurnedOn;
// Pressing the "2" key should start the color pulsing of the "LOK" company's logo.
extern bool logoNeedsToPulse;
extern float redColorComponentForPulsing;
// Pressing the "3" key should start the movement of the "LOK" company's logo to the right. Once it reaches the right
// edge of the window, it should appear on the left edge of the window.
extern bool logoNeedsToMoveRight;
// Pressing the "4" key should start the movement of the "LOK" company's logo in a circle.
extern bool logoNeedsToMoveInCircle;
// Pressing the "5" key should start the movement of the "LOK" company's logo from left to right and vice-versa between
// the window's edges. The closer the logo is to one of the edges, the more transparent it should be.
extern bool logoNeedsToMoveLeftRightBetweenEdges;
extern bool logoNowNeedsToMoveTowardsLeftEdge;
extern float bottomLeftXOfLogoText;
extern float bottomLeftYOfLogoText;

#endif
