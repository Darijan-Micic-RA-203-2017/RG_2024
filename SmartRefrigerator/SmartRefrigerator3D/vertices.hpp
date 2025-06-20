// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// vertices header. This prevents linking conflicts.
#ifndef VERTICES_H
#define VERTICES_H

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here
extern float verticesOfGrocery[288U];
extern float verticesOfChamber[2160U];
extern float verticesOfRefrigerator[1800U];
extern float verticesOfRefrigeratorDoor[6000U];
extern float verticesOfLightSourceInsideRefrigerator[108U];

#endif
