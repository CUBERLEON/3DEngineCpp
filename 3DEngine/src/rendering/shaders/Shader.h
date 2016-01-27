#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>
#include <vector>
#include "../resources/ShaderData.h"

class Transform;
class Material;
class RenderingEngine;
class DirectionalLight;
class PointLight;
class SpotLight;

class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void updateUniforms(Transform* transform, Material* material, RenderingEngine* renderingEngine);

	void bind() const { glUseProgram(m_data->getProgram()); }
protected:
	void setUniformI(const std::string& uniformName, int value) { glUniform1i(m_data->getUniformLocations()[uniformName], value); }
	void setUniformF(const std::string& uniformName, float value) { glUniform1f(m_data->getUniformLocations()[uniformName], value); }
	void setUniformV3F(const std::string& uniformName, const glm::vec3& value) { glUniform3f(m_data->getUniformLocations()[uniformName], value.x, value.y, value.z); }
	void setUniform3F(const std::string& uniformName, float x, float y, float z) { glUniform3f(m_data->getUniformLocations()[uniformName], x, y, z); }
	void setUniformV2F(const std::string& uniformName, const glm::vec2& value) { glUniform2f(m_data->getUniformLocations()[uniformName], value.x, value.y); }
	void setUniform2F(const std::string& uniformName, float x, float y) { glUniform2f(m_data->getUniformLocations()[uniformName], x, y); }
	void setUniformM4F(const std::string& uniformName, const glm::mat4& value) { glUniformMatrix4fv(m_data->getUniformLocations()[uniformName], 1, GL_FALSE, glm::value_ptr(value)); }
	void setUniform(const std::string& uniformName, DirectionalLight* value);
	void setUniform(const std::string& uniformName, PointLight* value);
	void setUniform(const std::string& uniformName, SpotLight* value);
private:
	static std::map<std::string, ShaderData*> m_loadedShaders;
	ShaderData* m_data;

	std::string m_filePath;

	void addUniform(const GLSLvariable& uniform);
	void addAllUniforms(const std::string& text);

	std::vector<GLSLvariable> parseStruct(const std::string& structName, const std::string& text);

	inline void addVertexShaderFromFile(const std::string& fileName) { addVertexShader(loadShader(fileName)); }
	inline void addGeometryShaderFromFile(const std::string& fileName) { addGeometryShader(loadShader(fileName)); }
	inline void addFragmentShaderFromFile(const std::string& fileName) { addFragmentShader(loadShader(fileName)); }

	inline void addVertexShader(const std::string& text) { addShader(text, GL_VERTEX_SHADER); }
	inline void addGeometryShader(const std::string& text) { addShader(text, GL_GEOMETRY_SHADER); }
	inline void addFragmentShader(const std::string& text) { addShader(text, GL_FRAGMENT_SHADER); }

	void compileShader();
	void addShader(const std::string& text, int type);
	std::string loadShader(const std::string& filePath);
};
#endif // SHADER_H