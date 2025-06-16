#include "global_variables.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here

glm::mat4 modelMatrix = glm::mat4(1.0F);
glm::mat4 viewMatrix = glm::mat4(1.0F);
glm::mat4 projectionMatrix = glm::mat4(1.0F);
glm::mat4 normalMatrix = glm::mat4(1.0F);
// All settings are kept in an instance of the camera class.
Camera *camera = NULL;
