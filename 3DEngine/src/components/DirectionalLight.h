#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(DirectionalLight* r);
	DirectionalLight(const glm::vec3& color, float intensity);
	~DirectionalLight();

	glm::vec3 getDirection() const;
protected:
private:
};

#endif // DIRECTIONAL_LIGHT_H
