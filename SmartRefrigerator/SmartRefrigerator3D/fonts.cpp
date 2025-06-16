#include "fonts.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

Font *timesNewRomanFont = NULL;

int setUpFonts()
{
	timesNewRomanFont = new Font("Resources/Fonts/times.ttf", textVAO, textVBO);
	if (timesNewRomanFont->errorCode != 0)
	{
		return timesNewRomanFont->errorCode;
	}

	return 0;
}

// De-allocate the fonts using their destructors.
void destroyFonts()
{
	delete timesNewRomanFont;
}
