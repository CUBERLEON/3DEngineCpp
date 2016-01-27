#include "TextureData.h"

#include "../../core/Debug.h"
#include <string>

TextureData::TextureData()
{
	glGenBuffers(1, &m_id);
	m_referencesCount = 1;
}

TextureData::~TextureData()
{
	glDeleteBuffers(1, &m_id);
	Debug::info("TextureData(" + std::to_string(m_id) + ") was removed");
}

void TextureData::addReference()
{
	m_referencesCount++;
}

bool TextureData::deleteReference()
{
	m_referencesCount--;
	return m_referencesCount == 0;
}
