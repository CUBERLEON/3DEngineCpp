#include "PerspectiveCamera.h"

#include <glm/glm.hpp>
#include "../core/Input.h"
#include "../core/Transform.h"
#include "../rendering/Window.h"

PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar)
{
	m_projectionTransform = glm::perspective(fov, aspectRatio, zNear, zFar);
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::input(float time)
{
	Input* input = getWindow()->getInput();
	if (!m_isLocked) 
	{
		float moveValue = m_speed * time;

		if (input->getKey(GLFW_KEY_W))
			move(getTransform()->getForward(), moveValue);
		if (input->getKey(GLFW_KEY_S))
			move(getTransform()->getBack(), moveValue);
		if (input->getKey(GLFW_KEY_A))
			move(getTransform()->getLeft(), moveValue);
		if (input->getKey(GLFW_KEY_D))
			move(getTransform()->getRight(), moveValue);

		updateRotation();
	}

	if (input->getKey(GLFW_KEY_L)) {
		input->setMousePosition(getWindow()->getCenter());
		m_isLocked = !m_isLocked;
	}
}

void PerspectiveCamera::updateProjection(float fov, float aspectRatio, float zNear, float zFar)
{
	m_projectionTransform = glm::perspective(fov, aspectRatio, zNear, zFar);
}
