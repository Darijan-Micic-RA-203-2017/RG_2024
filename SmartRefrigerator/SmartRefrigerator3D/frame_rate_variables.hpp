// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// frame rate variables header. This prevents linking conflicts.
#ifndef FRAME_RATE_VARIABLES_H
#define FRAME_RATE_VARIABLES_H

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

// The current time (in seconds) after the initialization of the GLFW library.
extern float currentFrameTime;
// The time difference (in seconds) between the end of renderings of the current frame and the previous frame.
// All velocities should be multiplied with the delta time value. The result is that when we have a large delta time,
// meaning that the rendering of the last frame took longer than average, the velocity for that frame will be a bit
// higher to balance it all out. When using this approach, it does not matter if the user has a very fast or slow PC,
// the velocity will be balanced out accordingly so each user will have the same experience. 
extern float deltaTime;
extern float frameRate;
extern const float desiredMaxDeltaTime; // 1 / 60
// The time (in seconds) it took to render the previous frame.
extern float previousFrameTime;

#endif
