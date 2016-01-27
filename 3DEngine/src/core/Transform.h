#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera;

class Transform
{
public:
	Transform();
	Transform(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
	~Transform();

	void update();

	glm::mat4 getModelTransform() const;
	glm::mat4 getRealModelTransform() const;
	glm::mat4 getModelViewProjectionTransform(Camera* camera) const;

	Transform* rotate(const glm::quat& rotation);
	Transform* translate(const glm::vec3& translation);
	Transform* scale(const glm::vec3& scale);

	bool isChildrenUpdateNeeded();

	inline glm::vec3 getRealPosition() const { return m_realPosition; }
	inline glm::quat getRealRotation() const { return m_realRotation; }
	inline glm::vec3 getRealScale() const { return m_realScale; }

	inline glm::vec3 getPosition() const { return m_position; }
	inline Transform* setPosition(const glm::vec3& position) { m_position = position; return this; }
	inline Transform* setPosition(float x, float y, float z) { m_position = glm::vec3(x, y, z); return this; }

	inline glm::quat getRotation() const { return m_rotation; }
	inline Transform* setRotation(const glm::quat& rotation) { m_rotation = normalize(rotation); return this; }

	inline glm::vec3 getScale() const { return m_scale; }
	inline Transform* setScale(const glm::vec3& scale) { m_scale = scale; return this; }
	inline Transform* setScale(float x, float y, float z) { m_scale = glm::vec3(x, y, z); return this; }

	inline void setParent(Transform* parent) { m_parent = parent; }
	inline Transform* getParent() const { return m_parent; }

	glm::vec3 getLeft() const;
	glm::vec3 getRealLeft() const;
	glm::vec3 getRight() const;
	glm::vec3 getRealRight() const;
	glm::vec3 getForward() const;
	glm::vec3 getRealForward() const;
	glm::vec3 getBack() const;
	glm::vec3 getRealBack() const;
	glm::vec3 getUp() const;
	glm::vec3 getRealUp() const;
	glm::vec3 getDown() const;
	glm::vec3 getRealDown() const;
protected:
private:
	Transform* m_parent;

	glm::vec3 m_position;
	glm::quat m_rotation;
	glm::vec3 m_scale;

	glm::vec3 m_oldPosition;
	glm::quat m_oldRotation;
	glm::vec3 m_oldScale;

	glm::vec3 m_realPosition;
	glm::quat m_realRotation;
	glm::vec3 m_realScale;

	glm::mat4 m_modelTransform;
	glm::mat4 m_realModelTransform;

	bool m_needChildrenUpdate;

	bool hasChanged();
	void updateRealValues();
	void updateModelTransform();
};

#endif