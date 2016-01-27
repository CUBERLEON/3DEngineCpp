#include "Camera.h"

#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include "../core/Debug.h"
#include "../core/Transform.h"
#include "../core/CoreEngine.h"
#include "../core/Input.h"
#include "../rendering/RenderingEngine.h"
#include "../rendering/Window.h"

Camera::Camera()
{
	m_isLocked = false;
	m_sensitivity = 8.0f;
	m_speed = 6.0f;
}

Camera::~Camera()
{}

void Camera::updateRotation()
{
	float rotateValue = m_sensitivity / 10000.0f;
	Input* input = getWindow()->getInput();
	glm::vec2 center = getWindow()->getCenter();
	glm::vec2 delta = input->getMousePosition() - center;

	bool movedX = delta.x != 0;
	bool movedY = delta.y != 0;

	glm::quat qx, qy, qz;

	if (movedY)
		qx = glm::angleAxis(-rotateValue * delta.y, getTransform()->getRight());
	if (movedX)
		qy = glm::angleAxis(-rotateValue * delta.x, glm::vec3(0, 1, 0));

	if (input->getKey(GLFW_KEY_Q) ^ input->getKey(GLFW_KEY_E))
	{
		if (input->getKey(GLFW_KEY_Q))
			qz = glm::angleAxis(15 * rotateValue, getTransform()->getBack());
		if (input->getKey(GLFW_KEY_E))
			qz = glm::angleAxis(-15 * rotateValue, getTransform()->getBack());
	}

	getTransform()->rotate(qz * (qy * qx));

	if (movedX || movedY)
		input->setMousePosition(center);
}

void Camera::addToEngine(CoreEngine* engine)
{
	engine->getRenderingEngine()->addCamera(this);
}

glm::mat4 Camera::getViewProjectionTransform()
{
	glm::mat4& cameraTranslation = glm::translate(-getTransform()->getRealPosition());
	glm::mat4& cameraRotation = glm::transpose(glm::toMat4(getTransform()->getRealRotation()));

	glm::mat4& viewTransform = cameraRotation * cameraTranslation;

	return m_projectionTransform * viewTransform;
}

void Camera::move(const glm::vec3& direction, float value)
{
	getTransform()->translate(glm::normalize(direction) * value);
}
