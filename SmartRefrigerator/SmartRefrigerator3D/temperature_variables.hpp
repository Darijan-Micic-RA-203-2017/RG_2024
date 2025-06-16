// By using these several preprocessor directives at the top of the header file, the compiler is informed to only
// include and compile this header file if it hasn't been included yet. This applies even if multiple files include the
// temperature variables header. This prevents linking conflicts.
#ifndef TEMPERATURE_VARIABLES_H
#define TEMPERATURE_VARIABLES_H

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

extern const float minTemperatureOfFreezingChamber;
extern float currentTemperatureOfFreezingChamber;
extern const float maxTemperatureOfFreezingChamber;
extern const float minTemperatureOfRefrigeratingChamber;
extern float currentTemperatureOfRefrigeratingChamber;
extern const float maxTemperatureOfRefrigeratingChamber;
extern const float minAvgTemperatureOfRefrigerator;
extern float currentAvgTemperatureOfRefrigerator;
extern const float maxAvgTemperatureOfRefrigerator;

#endif
