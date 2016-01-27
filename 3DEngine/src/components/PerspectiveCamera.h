#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float aspectRatio, float zNear, float zFar);
	~PerspectiveCamera();

	inline float getFOV() const { return m_fov; }
	inline float getAspectRatio() const { return m_aspectRatio; }
	inline float getZNear() const { return m_zNear; }
	inline float getZFar() const { return m_zFar; }
protected:
	void input(float time) override;
	void updateProjection(float fov, float aspectRatio, float zNear, float zFar);
private:
	float m_fov;
	float m_aspectRatio;
	float m_zNear;
	float m_zFar;
};

#endif // PERSPECTIVE_CAMERA_H
