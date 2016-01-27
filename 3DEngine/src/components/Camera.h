#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <algorithm>
#include "Component.h"

class Transform;
class CoreEngine;

class Camera : public Component
{
public:
	void move(const glm::vec3& direction, float value);

	glm::mat4 getViewProjectionTransform();

	inline bool isLocked() const { return m_isLocked; }
	inline void setLock(bool lock) { m_isLocked = lock; }

	inline float getSpeed() const { return m_speed; }
	inline void setSpeed(float speed) { m_speed = std::max(0.5f, speed); }

	inline float getSensitivity() const { return m_sensitivity; }
	inline void setSensitivity(float sensitivity) { m_sensitivity = std::max(0.5f, sensitivity); }
protected:
	Camera();
	~Camera();

	bool m_isLocked;

	float m_sensitivity;
	float m_speed;

	glm::mat4 m_projectionTransform;

	void updateRotation();
private:
	void addToEngine(CoreEngine* engine) override;
};

#endif // CAMERA_H
