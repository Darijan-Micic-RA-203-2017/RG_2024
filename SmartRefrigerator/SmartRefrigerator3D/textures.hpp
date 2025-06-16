// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// textures header. This prevents linking conflicts.
#ifndef TEXTURES_H
#define TEXTURES_H

#include "texture.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

extern Texture *fishSticksPackage;
extern Texture *milkCartonBox;
extern Texture *blueSnowflakeIcon;

// Generate textures, set their wrapping and filtering parameters, load the images-to-become-textures from
// the file system and generate all the required mipmaps using the helper class.
int setUpTextures();
// De-allocate the textures using their destructors.
void destroyTextures();

#endif
