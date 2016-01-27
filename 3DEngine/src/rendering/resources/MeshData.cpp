#include "MeshData.h"

#include "../../core/Debug.h"

MeshData::MeshData(int indicesCount)
{
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ibo);
	m_indicesCount = indicesCount;
	m_referencesCount = 1;
}

MeshData::~MeshData()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	Debug::info("MeshData(" + std::to_string((int)m_vbo) + ", " + std::to_string((int)m_ibo) + ") was removed");
}

void MeshData::addReference()
{
	m_referencesCount++;
}

bool MeshData::deleteReference()
{
	m_referencesCount--;
	return m_referencesCount == 0;
}
