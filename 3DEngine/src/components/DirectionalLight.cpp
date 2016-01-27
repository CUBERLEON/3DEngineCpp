#include "DirectionalLight.h"

#include "../core/Debug.h"
#include "../core/Transform.h"
#include "../rendering/shaders/Shader.h"

DirectionalLight::DirectionalLight(DirectionalLight* r)
: DirectionalLight(r->getColor(), r->getIntensity())
{}

DirectionalLight::DirectionalLight(const glm::vec3& color, float intensity)
: Light(color, intensity)
{
	setShader(new Shader("forward-directional"));
}

DirectionalLight::~DirectionalLight()
{
}

glm::vec3 DirectionalLight::getDirection() const
{
	return glm::rotate(getTransform()->getRealRotation(), glm::vec3(0, 0, -1));
}
