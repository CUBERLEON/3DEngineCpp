#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include "Component.h"

class Shader;

class Light : public Component
{
public:
	inline Shader* getShader() const { return m_shader; }

	inline glm::vec3 getColor() const { return m_color; }
	virtual inline void setColor(const glm::vec3& color) { m_color = color; }

	inline float getIntensity() const { return m_intensity; }
	virtual inline void setIntensity(float intensity) { m_intensity = intensity; }
protected:
	Light(const glm::vec3& color, float intensity);
	~Light();

	glm::vec3 m_color;
	float m_intensity;
	Shader* m_shader;

	inline void setShader(Shader* shader) { m_shader = shader; }
private:
	void addToEngine(CoreEngine* engine) override;
};

#endif // LIGHT_H
