#include "textures.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

Texture *fishSticksPackage = NULL;
Texture *milkCartonBox = NULL;
Texture *blueSnowflakeIcon = NULL;

// Generate textures, set their wrapping and filtering parameters, load the images-to-become-textures from
// the file system and generate all the required mipmaps using the helper class.
int setUpTextures()
{
	fishSticksPackage = new Texture("Resources/Images/Fish_sticks_package.png", false);
	if (fishSticksPackage->errorCode)
	{
		return fishSticksPackage->errorCode;
	}
	milkCartonBox = new Texture("Resources/Images/Milk_carton_box.png", false);
	if (milkCartonBox->errorCode)
	{
		return milkCartonBox->errorCode;
	}
	blueSnowflakeIcon = new Texture("Resources/Images/Blue_snowflake_icon.png", true);
	if (blueSnowflakeIcon->errorCode)
	{
		return blueSnowflakeIcon->errorCode;
	}

	return 0;
}

// De-allocate the textures using their destructors.
void destroyTextures()
{
	delete blueSnowflakeIcon;
	delete milkCartonBox;
	delete fishSticksPackage;
}
