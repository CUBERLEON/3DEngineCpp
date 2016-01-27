#include "Container.h"

#include "../core/Debug.h"
#include "Texture.h"

Container::Container()
{
	
}

Container::~Container()
{
	Debug::info("Container destructor");
// 	for (Texture texture : m_textures.values())
// 		texture.dispose();
}

Texture* Container::getTexture(std::string name)
{
	return m_textures[name];
}
