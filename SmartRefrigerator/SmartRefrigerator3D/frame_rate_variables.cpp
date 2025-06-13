#include "frame_rate_variables.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The current time (in seconds) after the initialization of the GLFW library.
float currentFrameTime = 0.0F;
// The time difference (in seconds) between the end of renderings of the current frame and the previous frame.
// All velocities should be multiplied with the delta time value. The result is that when we have a large delta time,
// meaning that the rendering of the last frame took longer than average, the velocity for that frame will be a bit
// higher to balance it all out. When using this approach, it does not matter if the user has a very fast or slow PC,
// the velocity will be balanced out accordingly so each user will have the same experience. 
float deltaTime = 0.0F;
float frameRate = 0.0F;
const float desiredMaxDeltaTime = 0.016667F; // 1 / 60
// The time (in seconds) it took to render the previous frame.
float previousFrameTime = 0.0F;
