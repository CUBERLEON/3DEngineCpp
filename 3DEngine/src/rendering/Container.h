#pragma once

#include "glm\glm.hpp"
#include <string>
#include <map>

class Texture;

class Container
{
public:
	Container();
	~Container();

	inline Container* addTexture(std::string name, Texture* value) { m_textures[name] = value; return this; }
	inline Container* addVector3f(std::string name, glm::vec3 value) { m_vector3fs[name] = value; return this; }
	inline Container* addFloat(std::string name, float value) { m_floats[name] = value; return this; }
	inline Container* addInteger(std::string name, int value) { m_integers[name] = value; return this; }

	Texture* getTexture(std::string name);
	inline glm::vec3 getVector3f(std::string name) { return m_vector3fs[name]; }
	inline float getFloat(std::string name) { return m_floats[name]; }
	inline int getInteger(std::string name) { return m_integers[name]; }
protected:
private:
	std::map<std::string, Texture*> m_textures;
	std::map<std::string, glm::vec3> m_vector3fs;
	std::map<std::string, float> m_floats;
	std::map<std::string, int> m_integers;
};

