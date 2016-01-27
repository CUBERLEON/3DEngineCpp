#pragma once

#include <GL/glew.h>

class MeshData
{
public:
	MeshData(int indicesCount);
	~MeshData();

	void addReference();
	bool deleteReference();

	inline GLuint getVertexBufferID() { return m_vbo; }
	inline GLuint getIndicesBufferID() { return m_ibo; }
	inline int getIndicesCount() { return m_indicesCount; }
protected:
private:
	GLuint m_vbo;
	GLuint m_ibo;
	int m_indicesCount;

	int m_referencesCount;
};

