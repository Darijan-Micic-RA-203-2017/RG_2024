#include "shader_programs.hpp"

// REFERENCE: https://cplusplus.com/forum/general/131319/#msg707907
// REFERENCE: https://stackoverflow.com/questions/56735173/variable-already-defined-in-obj-what-is-going-on-here
ShaderProgram *shaderProgramForGrocery = NULL;
ShaderProgram *shaderProgramForChamber = NULL;
ShaderProgram *shaderProgramForRefrigerator = NULL;
ShaderProgram *shaderProgramForLightSourceInsideRefrigerator = NULL;
ShaderProgram *shaderProgramForNonlogoText = NULL;
ShaderProgram *shaderProgramForLogoText = NULL;

int compileShadersAndLinkShaderPrograms()
{
	shaderProgramForGrocery = new ShaderProgram("Shaders/Grocery/vertex_shader_of_grocery.glsl", 
		"Shaders/Grocery/fragment_shader_of_grocery.glsl");
	if (shaderProgramForGrocery->errorCode != 0)
	{
		return shaderProgramForGrocery->errorCode;
	}
	shaderProgramForChamber = new ShaderProgram("Shaders/Chamber/vertex_shader_of_chamber.glsl", 
		"Shaders/Chamber/fragment_shader_of_chamber.glsl");
	if (shaderProgramForChamber->errorCode != 0)
	{
		return shaderProgramForChamber->errorCode;
	}
	shaderProgramForRefrigerator = new ShaderProgram("Shaders/Refrigerator/vertex_shader_of_refrigerator.glsl", 
		"Shaders/Refrigerator/fragment_shader_of_refrigerator.glsl");
	if (shaderProgramForRefrigerator->errorCode != 0)
	{
		return shaderProgramForRefrigerator->errorCode;
	}
	shaderProgramForLightSourceInsideRefrigerator = new ShaderProgram(
		"Shaders/LightSourceInsideRefrigerator/vertex_shader_of_light_source_inside_refrigerator.glsl", 
		"Shaders/LightSourceInsideRefrigerator/fragment_shader_of_light_source_inside_refrigerator.glsl");
	if (shaderProgramForLightSourceInsideRefrigerator->errorCode != 0)
	{
		return shaderProgramForLightSourceInsideRefrigerator->errorCode;
	}
	shaderProgramForNonlogoText = new ShaderProgram("Shaders/NonlogoText/vertex_shader_of_nonlogo_text.glsl", 
		"Shaders/NonlogoText/fragment_shader_of_nonlogo_text.glsl");
	if (shaderProgramForNonlogoText->errorCode != 0)
	{
		return shaderProgramForNonlogoText->errorCode;
	}
	shaderProgramForLogoText = new ShaderProgram("Shaders/LogoText/vertex_shader_of_logo_text.glsl", 
		"Shaders/LogoText/fragment_shader_of_logo_text.glsl");
	if (shaderProgramForLogoText->errorCode != 0)
	{
		return shaderProgramForLogoText->errorCode;
	}

	return 0;
}
