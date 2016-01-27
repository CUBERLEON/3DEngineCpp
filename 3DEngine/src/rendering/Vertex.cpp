#include "Vertex.h"

#include "../core/Debug.h"

Vertex::Vertex(glm::vec3 position)
: Vertex(position, glm::vec2(-1, -1), glm::vec3(0, 0, 0))
{
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texCoord)
: Vertex(position, texCoord, glm::vec3(0, 0, 0))
{
}

Vertex::Vertex(glm::vec3 position, glm::vec2 texCoord, glm::vec3 normal)
{
	m_position = position;
	m_texCoord = texCoord;
	m_normal = normal;
}

Vertex::~Vertex()
{
// 	Debug::info("removing Vertex(pos{%.2f, %.2f, %.2f}, tex_coord{%.2f, %.2f}, norm{%.2f, %.2f, %.2f})", 
// 		m_position.x, m_position.y, m_position.z, m_texCoord.x, m_texCoord.y, m_normal.x, m_normal.y, m_normal.z);
}
