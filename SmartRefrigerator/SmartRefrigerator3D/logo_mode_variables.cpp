# include "logo_mode_variables.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The logo mode starts 5 seconds after the user last clicked on the refrigerator's graphic display and ends when the
// user clicks on it again. Logo mode consists of showing the "LOK" company logo over the screen.
bool logoModeTurnedOn = false;
// Pressing the "2" key should start the color pulsing of the "LOK" company's logo.
bool logoNeedsToPulse = false;
float redColorComponentForPulsing = 0.0F;
// Pressing the "3" key should start the movement of the "LOK" company's logo to the right. Once it reaches the right
// edge of the window, it should appear on the left edge of the window.
bool logoNeedsToMoveRight = false;
// Pressing the "4" key should start the movement of the "LOK" company's logo in a circle.
bool logoNeedsToMoveInCircle = false;
// Pressing the "5" key should start the movement of the "LOK" company's logo from left to right and vice-versa between
// the window's edges. The closer the logo is to one of the edges, the more transparent it should be.
bool logoNeedsToMoveLeftRightBetweenEdges = false;
bool logoNowNeedsToMoveTowardsLeftEdge = true;
float bottomLeftXOfLogoText = 0.275F * static_cast<float>(windowWidth);
float bottomLeftYOfLogoText = 0.4F * static_cast<float>(windowHeight);
