#include "PointLight.h"

#include <cmath>
#include <algorithm>
#include "../rendering/shaders/Shader.h"

PointLight::PointLight(PointLight* r)
: PointLight(r->getColor(), r->getIntensity(), r->getAttenuation(), r->getRange())
{
}

PointLight::PointLight(const glm::vec3& color, float intensity, Attenuation* attenuation)
: PointLight(color, intensity, attenuation, 0)
{
	updateRange();
}

PointLight::PointLight(const glm::vec3& color, float intensity, Attenuation* attenuation, float range)
: Light(color, intensity)
{
	m_attenuation = attenuation;
	m_range = range;
	setShader(new Shader("forward-point"));
}

void PointLight::updateRange()
{
	float minIntensity = 1 / (m_intensity * std::max(m_color.x, std::max(m_color.y, m_color.z)) * 256);
	float maxRange = 1000.0f;

	float range = maxRange;

	float c = getAttenuation()->getConstant();
	float l = getAttenuation()->getLinear();
	float e = getAttenuation()->getExponent();
	if (m_intensity < minIntensity * c) 
		range = 0;
	else 
		if (e > 0) 
			range = (-l + (float)std::sqrt(l * l + 4.0 * e * (m_intensity / minIntensity - c))) / (2.0f * e);
		else if (l > 0)
			range = std::max(.0f, (m_intensity - minIntensity * c) / (minIntensity * l));

	m_range = std::min(range, maxRange);
}

PointLight::~PointLight()
{
}

void PointLight::setIntensity(float intensity)
{
	m_intensity = std::max(.0f, intensity);
	updateRange();
}
