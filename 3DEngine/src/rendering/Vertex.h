#pragma once

#include <glm\glm.hpp>

class Vertex
{
public:
	static const size_t SIZE = 8;

	Vertex(glm::vec3 position);
	Vertex(glm::vec3 position, glm::vec2 texCoord);
	Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal);

	~Vertex();

	inline glm::vec3& getPosition() { return m_position; }
	inline void setPosition(glm::vec3 m_pos) { m_position = m_pos; }

	inline glm::vec2& getTexCoord() { return m_texCoord; }
	inline void setTexCoord(glm::vec2 texCoord) { m_texCoord = texCoord; }

	inline glm::vec3& getNormal() { return m_normal; }
	inline void setNormal(glm::vec3 normal) { m_normal = normal; }
protected:
private:
	glm::vec3 m_position;
	glm::vec2 m_texCoord;
	glm::vec3 m_normal;
};

