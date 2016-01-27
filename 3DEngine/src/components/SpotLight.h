#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include <glm/glm.hpp>
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	SpotLight(SpotLight* r);
	SpotLight(const glm::vec3& color, float intensity, Attenuation* attenuation, float cutoff);
	SpotLight(PointLight* pointLight, float cutoff);
	~SpotLight();

	glm::vec3 getDirection() const;

	inline float getCutoff() const { return m_cutoff; }
	inline void setCutoff(float cutoff) { m_cutoff = cutoff; }
protected:
	float m_cutoff;

	SpotLight(const glm::vec3& color, float intensity, Attenuation* attenuation, float range, float cutoff);
private:
};

#endif // SPOT_LIGHT_H
