#version 330 core

// REFERENCE: https://learnopengl.com/Lighting/Light-casters
struct Spotlight
{
	vec3 direction;
	vec3 position;
	float cosOfInnerCutoffAngle;
	float cosOfOuterCutoffAngle;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float kC;
	float kL;
	float kQ;
};

struct Material
{
	float shininessOfSpecularHighlight;
};

in vec3 FragPos;
in vec3 Normal;
in vec4 Color;

out vec4 FragColor;

uniform bool seeThroughModeTurnedOn;
uniform float windowWidth;
uniform float windowHeight;
uniform float currentTemperatureOfFreezingChamber;
uniform float currentTemperatureOfRefrigeratingChamber;
// Should the scene be lit at all?
uniform bool sceneLit;
// Pass the position of viewer (needed for specular component of the Phong's lighting model).
uniform vec3 positionOfViewer;
// Pass the spotlight.
uniform Spotlight lightSourceInsideRefrigerator;
// Pass the material of object (needed for all 3 components of the Phong's lighting model).
uniform Material material;
// Strength of the light shining the scene.
uniform float intensityOfBackgroundLight;
// REFERENCE: https://learnopengl.com/Advanced-OpenGL/Advanced-GLSL
/*
layout (std140) uniform RequiredLightingData
{
	// Should the scene be lit at all?
	bool sceneLit;
	// Pass the position of viewer (needed for specular component of the Phong's lighting model).
	vec3 positionOfViewer;
	// Pass the spotlight.
	Spotlight lightSourceInsideRefrigerator;
	// Pass the material of object (needed for all 3 components of the Phong's lighting model).
	Material material;
	// Strength of the light shining the scene.
	float intensityOfBackgroundLight;
};
*/

void main()
{
	vec4 color = vec4(Color.xyz, 1.0F);
	if (seeThroughModeTurnedOn)
	{
		const float minTemperatureOfFreezingChamber = -40.0F;
		const float maxTemperatureOfFreezingChamber = -18.0F;
		const float minTemperatureOfRefrigeratingChamber = 0.0F;
		const float maxTemperatureOfRefrigeratingChamber = 7.0F;

		// The built-in "gl_FragCoord" vector variable has its x-value and y-value in screen-space coordinates.
		// Because of that, the normalized device coordinates (NDCs) used to describe the vertex's position in
		// the main program have to be converted to the [0.0F, 1.0F] range and multiplied with window's
		// width/height. Only then can the single values of the "gl_FragCoord" vector be compared with the
		// borders of the chambers.
		if (gl_FragCoord.y >= 0.393333F * windowHeight && gl_FragCoord.y <= 0.603333F * windowHeight)
		{
			// minFreezChmbT <= currFreezChmbT <= maxFreezChmbT / + (-left_side)
			// 0.0F <= currFreezChmbT - minFreezChmbT <= maxFreezChmbT - minFreezChmbT / : right_side
			// 0.0F <= (currFreezChmbT - minFreezChmbT) / (maxFreezChmbT - minFreezChmbT) <= 1.0F
			// resultingColorOfFragment.a = (1.0F - the_expression_in_the_middle) / 2.0F.
			color.a = (1.0F - (currentTemperatureOfFreezingChamber - minTemperatureOfFreezingChamber) / 
				(maxTemperatureOfFreezingChamber - minTemperatureOfFreezingChamber)) / 2.0F;
		}
		else
		{
			// minRefrigChmbT <= currRefrigChmbT <= maxRefrigChmbT / + (-left_side)
			// 0.0F <= currRefrigChmbT - minRefrigChmbT <= maxRefrigChmbT - minRefrigChmbT / : right_side
			// 0.0F <= (currRefrigChmbT - minRefrigChmbT) / (maxRefrigChmbT - minRefrigChmbT) <= 1.0F
			// resultingColorOfFragment.a = (1.0F - the_expression_in_the_middle) / 2.0F.
			color.a = (1.0F - 
				(currentTemperatureOfRefrigeratingChamber - minTemperatureOfRefrigeratingChamber) / 
					(maxTemperatureOfRefrigeratingChamber - minTemperatureOfRefrigeratingChamber)) / 2.0F;
		}
	}
	else
	{
		color.a = Color.a;
	}

	if (!sceneLit)
	{
		FragColor = vec4(intensityOfBackgroundLight * color.rgb, color.a);

		return;
	}

	vec3 ambientColor = lightSourceInsideRefrigerator.ambientColor * vec3(color);

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightSourceInsideRefrigerator.position - FragPos);
	float diffuseFactor = max(0.0F, dot(normal, lightDirection));
	vec3 diffuseColor = lightSourceInsideRefrigerator.diffuseColor * diffuseFactor * vec3(color);

	vec3 viewDirection = normalize(positionOfViewer - FragPos);
	// REFERENCE: https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
	vec3 halfwayVectorBetweenLightAndViewDirections = normalize(lightDirection + viewDirection);
	float specularFactor = pow(max(0.0F, dot(normal, halfwayVectorBetweenLightAndViewDirections)), 
		material.shininessOfSpecularHighlight);
	vec3 specularColor = lightSourceInsideRefrigerator.specularColor * specularFactor * vec3(color);

	float cosOfAngleBetweenLightDirAndSpotDir = 
		max(0.0F, dot(lightDirection, normalize(-lightSourceInsideRefrigerator.direction)));
	float epsilon = 
		lightSourceInsideRefrigerator.cosOfInnerCutoffAngle - lightSourceInsideRefrigerator.cosOfOuterCutoffAngle;
	float edgeSmoothingFactor = clamp(
		(cosOfAngleBetweenLightDirAndSpotDir - lightSourceInsideRefrigerator.cosOfOuterCutoffAngle) / epsilon, 
			0.0F, 1.0F);
	diffuseColor *= edgeSmoothingFactor;
	specularColor *= edgeSmoothingFactor;

	float d = length(lightSourceInsideRefrigerator.position - FragPos);
	float attenuationFactor = 1.0F / (lightSourceInsideRefrigerator.kC 
		+ lightSourceInsideRefrigerator.kL * d + lightSourceInsideRefrigerator.kQ * pow(d, 2.0F));
	diffuseColor *= attenuationFactor;
	specularColor *= attenuationFactor;

	vec3 resultingColorOfFragment = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(intensityOfBackgroundLight * resultingColorOfFragment, color.a);
}
