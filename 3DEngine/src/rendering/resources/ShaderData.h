#pragma once

#include "GL/glew.h"
#include <map>
#include <string>
#include <vector>
#include "../shaders/GLSLvariable.h"

class ShaderData
{
public:
	ShaderData();
	~ShaderData();

	void addReference();
	bool deleteReference();

	inline GLuint getProgram() { return m_program; }
	inline std::map<std::string, int>& getUniformLocations() { return m_uniformLocations; }
	inline std::vector<GLSLvariable>& getUniforms() { return m_uniforms; }
//    inline std::vector<GLSLvariable>& getAllUniforms() { return m_allUniforms; }
protected:
private:
	GLuint m_program;

	std::map<std::string, int> m_uniformLocations;
	std::vector<GLSLvariable> m_uniforms; //without sub GLSLvariables
//    std::vector<GLSLvariable> m_allUniforms; //all GLSLvariables

	int m_referencesCount;
};

