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

void main()
{
	if (!sceneLit)
	{
		FragColor = vec4(intensityOfBackgroundLight * Color.rgb, Color.a);

		return;
	}

	vec3 ambientColor = lightSourceInsideRefrigerator.ambientColor * vec3(Color);

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightSourceInsideRefrigerator.position - FragPos);
	float diffuseFactor = max(0.0F, dot(normal, lightDirection));
	vec3 diffuseColor = lightSourceInsideRefrigerator.diffuseColor * diffuseFactor * vec3(Color);

	vec3 viewDirection = normalize(positionOfViewer - FragPos);
	// REFERENCE: https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
	vec3 halfwayVectorBetweenLightAndViewDirections = normalize(lightDirection + viewDirection);
	float specularFactor = pow(max(0.0F, dot(normal, halfwayVectorBetweenLightAndViewDirections)), 
		material.shininessOfSpecularHighlight);
	vec3 specularColor = lightSourceInsideRefrigerator.specularColor * specularFactor * vec3(Color);

	float cosOfAngleBetweenLightDirAndSpotDir = 
		max(0.0F, dot(lightDirection, normalize(-lightSourceInsideRefrigerator.direction)));
	float epsilon = 
		lightSourceInsideRefrigerator.cosOfInnerCutoffAngle - lightSourceInsideRefrigerator.cosOfOuterCutoffAngle;
	float edgeSmoothingFactor = clamp(
		(cosOfAngleBetweenLightDirAndSpotDir - lightSourceInsideRefrigerator.cosOfOuterCutoffAngle) / epsilon, 0.0F, 1.0F);
	diffuseColor *= edgeSmoothingFactor;
	specularColor *= edgeSmoothingFactor;

	float d = length(lightSourceInsideRefrigerator.position - FragPos);
	float attenuationFactor = 1.0F / (lightSourceInsideRefrigerator.kC + lightSourceInsideRefrigerator.kL * d 
		+ lightSourceInsideRefrigerator.kQ * pow(d, 2.0F));
	diffuseColor *= attenuationFactor;
	specularColor *= attenuationFactor;

	vec3 resultingColorOfFragment = ambientColor + diffuseColor + specularColor;
	FragColor = vec4(intensityOfBackgroundLight * resultingColorOfFragment, Color.a);
}
