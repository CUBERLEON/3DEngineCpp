#include "ShaderData.h"

#include "../../core/Debug.h"

ShaderData::ShaderData()
{
	m_program = glCreateProgram();

	if (m_program == 0)
		Debug::fatalError("shader program creation failed");

// 	m_allUniforms = new ArrayList<>();

	m_referencesCount = 1;
}

ShaderData::~ShaderData()
{
	glDeleteProgram(m_program);
	m_uniforms.clear();
	m_uniformLocations.clear();
	Debug::info("ShaderData(" + std::to_string(m_program) + ") was removed");
}

void ShaderData::addReference()
{
	m_referencesCount++;
}

bool ShaderData::deleteReference()
{
	m_referencesCount--;
	return m_referencesCount == 0;
}
