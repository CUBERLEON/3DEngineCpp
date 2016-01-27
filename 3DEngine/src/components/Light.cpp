#include "Light.h"

#include "../core/Debug.h"
#include "../core/CoreEngine.h"
#include "../rendering/RenderingEngine.h"

Light::Light(const glm::vec3& color, float intensity)
{
	m_color = color;
	m_intensity = intensity;
}

Light::~Light()
{
	delete m_shader;
}

void Light::addToEngine(CoreEngine* engine)
{
	engine->getRenderingEngine()->addLight(this);
}