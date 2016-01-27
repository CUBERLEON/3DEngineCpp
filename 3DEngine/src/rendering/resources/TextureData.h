#pragma once

#include "GL/glew.h"

class TextureData
{
public:
	TextureData();
	~TextureData();

	void addReference();
	bool deleteReference();

	inline GLuint getBufferID() { return m_id; }
protected:
private: 
	GLuint m_id;

	int m_referencesCount;
};