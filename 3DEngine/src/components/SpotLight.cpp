#include "SpotLight.h"

#include "../core/Transform.h"
#include "../rendering/shaders/Shader.h"

SpotLight::SpotLight(SpotLight* r)
: SpotLight(r->getColor(), r->getIntensity(), r->getAttenuation(), r->getRange(), r->getCutoff())
{
}

SpotLight::SpotLight(const glm::vec3& color, float intensity, Attenuation* attenuation, float cutoff)
: PointLight(color, intensity, attenuation)
{
	m_cutoff = cutoff;
	setShader(new Shader("forward-spot"));
}

SpotLight::SpotLight(PointLight* pointLight, float cutoff)
: SpotLight(pointLight->getColor(), pointLight->getIntensity(), pointLight->getAttenuation(), pointLight->getRange(), cutoff)
{
}

SpotLight::SpotLight(const glm::vec3& color, float intensity, Attenuation* attenuation, float range, float cutoff) : 
PointLight(color, intensity, attenuation, range)
{
	m_cutoff = cutoff;
	setShader(new Shader("forward-spot"));
}

SpotLight::~SpotLight()
{
}

glm::vec3 SpotLight::getDirection() const
{
	return glm::rotate(getTransform()->getRealRotation(), glm::vec3(0, 0, -1));
}
