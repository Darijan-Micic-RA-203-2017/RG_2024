// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// fonts header. This prevents linking conflicts.
#ifndef FONTS_H
#define FONTS_H

#include "array_and_buffer_objects.hpp"
#include "text.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

extern Font *timesNewRomanFont;

int setUpFonts();
// De-allocate the fonts using their destructors.
void destroyFonts();

#endif
