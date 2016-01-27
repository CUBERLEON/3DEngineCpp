#include "Shader.h"

#include <regex>
#include <fstream>
#include "../Material.h"
#include "../RenderingEngine.h"
#include "../Texture.h"
#include "../../core/Debug.h"
#include "../../core/Transform.h"
#include "../../components/Camera.h"
#include "../../components/Light.h"
#include "../../components/DirectionalLight.h"
#include "../../components/PointLight.h"
#include "../../components/SpotLight.h"

Shader::Shader(const std::string& filePath)
{
	m_filePath = filePath;

	if (m_loadedShaders.count(filePath) && (m_data = m_loadedShaders[filePath]) != nullptr) 
	{
		m_data->addReference();
	}
	else 
	{
		m_data = new ShaderData();
		m_loadedShaders[filePath] = m_data;

		std::string vertexShaderSource = loadShader(filePath + ".vs");
		std::string fragmentShaderSource = loadShader(filePath + ".fs");

		addVertexShader(vertexShaderSource);
		addFragmentShader(fragmentShaderSource);

		compileShader();

		addAllUniforms(vertexShaderSource);
		addAllUniforms(fragmentShaderSource);

		Debug::info("Shader('%s') was loaded", m_filePath.c_str());
	}
}

Shader::~Shader()
{
// 		if (m_data->deleteReference()) {
// 			if (m_filePath != null) {
// 				m_loadedShaders.remove(m_filePath, m_data);
// 			}
// 		}
// 		if (m_data != null)
// 			m_data->dispose();
// 		Debug.info("Shader(" + m_filePath + ") was deleted (finalize)");
}

void Shader::updateUniforms(Transform* transform, Material* material, RenderingEngine* renderingEngine)
{
	for (GLSLvariable variable : m_data->getUniforms()) 
	{
		switch (variable.name[0])
		{
			//transform uniforms
			case 't': 
			{
				if (variable.name == "t_mvpTransform" && variable.type == "mat4")
					setUniformM4F("t_mvpTransform", transform->getModelViewProjectionTransform(renderingEngine->getMainCamera()));
				else if (variable.name == "t_mTransform" && variable.type == "mat4")
					setUniformM4F("t_mTransform", transform->getRealModelTransform());
				break;
			}
			//material uniforms
			case 'm': 
			{
				if (variable.name == "m_diffuse" && variable.type == "sampler2D")
					material->getTexture("diffuse")->bind(renderingEngine->getInteger("diffuse"));
				else if (variable.name == "m_specularIntensity" && variable.type == "float")
					setUniformF("m_specularIntensity", material->getFloat("specularIntensity"));
				else if (variable.name == "m_specularPower" && variable.type == "float")
					setUniformF("m_specularPower", material->getFloat("specularPower"));
				break;
			}
			//light uniforms
			case 'l':
			{
				if (variable.name == "l_ambient" && variable.type == "vec3")
					setUniformV3F("l_ambient", renderingEngine->getVector3f("ambientLight"));
				else if (variable.name == "l_directional" && variable.type == "DirectionalLight")
					setUniform("l_directional", (DirectionalLight*)(renderingEngine->getActiveLight()));
				else if (variable.name == "l_point" && variable.type == "PointLight")
					setUniform("l_point", (PointLight*)(renderingEngine->getActiveLight()));
				else if (variable.name == "l_spot" && variable.type == "SpotLight")
					setUniform("l_spot", (SpotLight*)(renderingEngine->getActiveLight()));
				break;
			}
			//additional vertex shader uniforms
			case 'v': 
			{

				break;
			}
			//additional fragment shader uniforms
			case 'f': 
			{
				if (variable.name == "f_eyePosition" && variable.type == "vec3")
					setUniformV3F("f_eyePosition", renderingEngine->getMainCamera()->getTransform()->getRealPosition());
				break;
			}
		}
	}
}

void Shader::setUniform(const std::string& uniformName, DirectionalLight* value)
{
	setUniformV3F(uniformName + ".color", value->getColor());
	setUniformF(uniformName + ".intensity", value->getIntensity());
	setUniformV3F(uniformName + ".direction", value->getDirection());
}

void Shader::setUniform(const std::string& uniformName, PointLight* value)
{
	setUniformV3F(uniformName + ".color", value->getColor());
	setUniformF(uniformName + ".intensity", value->getIntensity());
	setUniformF(uniformName + ".attenuation.constant", value->getAttenuation()->getConstant());
	setUniformF(uniformName + ".attenuation.linear", value->getAttenuation()->getLinear());
	setUniformF(uniformName + ".attenuation.exponent", value->getAttenuation()->getExponent());
	setUniformV3F(uniformName + ".position", value->getTransform()->getPosition());
	setUniformF(uniformName + ".range", value->getRange());
}

void Shader::setUniform(const std::string& uniformName, SpotLight* value)
{
	setUniform(uniformName + ".pointLight", (PointLight*)value);
	setUniformV3F(uniformName + ".direction", value->getDirection());
	setUniformF(uniformName + ".cutoff", value->getCutoff());
}

std::map<std::string, ShaderData*> Shader::m_loadedShaders = {};

void Shader::addUniform(const GLSLvariable& uniform)
{
	int uniformLocation = glGetUniformLocation(m_data->getProgram(), uniform.name.c_str());

	if (uniformLocation == -1)
		Debug::error("Unnecessary uniform '" + uniform.name + "' in Shader(path='" + m_filePath + "')");
	else
		m_data->getUniformLocations()[uniform.name] = uniformLocation;
}

void Shader::addAllUniforms(const std::string& text)
{
	std::smatch m;
	std::string subText = text;
	while (std::regex_search(subText, m, std::regex("uniform\\s+([^\\s]+)\\s+([^\\s]+)\\s*;")))
	{
		GLSLvariable uniform(m[1], m[2]);

		m_data->getUniforms().push_back(uniform);

		std::vector<GLSLvariable>& subUniforms = parseStruct(uniform.type, text);
		if (subUniforms.size() == 0) 
		{
			addUniform(uniform);
// 			m_allUniforms.add(uniform);
		}
		else for (GLSLvariable subUniform : subUniforms) 
		{
			addUniform(GLSLvariable(subUniform.type, uniform.name + "." + subUniform.name));
// 			m_allUniforms.add(new GLSLvariable(subUniform.type, uniform.name + "." + subUniform.name));
		}

		subText = m.suffix();
	}
}

std::vector<GLSLvariable> Shader::parseStruct(const std::string& structName, const std::string& text)
{
	std::vector<GLSLvariable> res;
	std::smatch m;
	if (!std::regex_search(text, m, std::regex("struct\\s+" + structName + "\\s+\\{([^\\}]*)\\};")))
		return res;
	else {
		std::string structFields = m[1];
		while (std::regex_search(structFields, m, std::regex("([^\\s]+)\\s+([^\\s]+)\\s*;"))) 
		{
			GLSLvariable variable(m[1], m[2]);

			std::vector<GLSLvariable> &subVariables = parseStruct(variable.type, text);
			if (subVariables.size() == 0)
				res.push_back(variable);
			else
			for (GLSLvariable subVariable : subVariables)
				res.push_back(GLSLvariable(subVariable.type, variable.name + "." + subVariable.name));

			structFields = m.suffix();
		}

		return res;
	}
}

void Shader::compileShader()
{
	GLint param;
	GLchar info[1024];
	glLinkProgram(m_data->getProgram());
	glGetProgramiv(m_data->getProgram(), GL_LINK_STATUS, &param);
	if (param == GL_FALSE)
	{
		glGetShaderInfoLog(m_data->getProgram(), 1024, GLsizei(), info);
		Debug::fatalError(info);
	}

	glValidateProgram(m_data->getProgram());
	glGetProgramiv(m_data->getProgram(), GL_VALIDATE_STATUS, &param);
	if (param == GL_FALSE)
	{
		glGetShaderInfoLog(m_data->getProgram(), 1024, GLsizei(), info);
		Debug::fatalError(info);
	}
}

void Shader::addShader(const std::string& text, int type)
{
	int shader = glCreateShader(type);

	std::string shaderType;
	if (type == GL_VERTEX_SHADER) shaderType = "GL_VERTEX_SHADER";
	else if (type == GL_FRAGMENT_SHADER) shaderType = "GL_FRAGMENT_SHADER";
	else if (type == GL_GEOMETRY_SHADER) shaderType = "GL_GEOMETRY_SHADER";
	else shaderType = std::to_string(type);

	if (shader == 0)
		Debug::fatalError("Could not find valid memory location when adding Shader(type='" + shaderType + "' path='" + m_filePath + "')");

	GLchar const* files[] = { text.c_str() };
	GLint param;
	glShaderSource(shader, 1, files, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
	if (param == GL_FALSE)
	{
		GLchar info[1024];
		glGetShaderInfoLog(m_data->getProgram(), 1024, GLsizei(), info);
		Debug::fatalError("Shader(type='" + shaderType + "' path='" + m_filePath + "') compilation failed\n" + info);
	}

	glAttachShader(m_data->getProgram(), shader);
}

std::string Shader::loadShader(const std::string& filePath)
{
	std::string shaderSource = "";
	try
	{
		std::ifstream file("./res/shaders/" + filePath);
		std::string line;
		while (std::getline(file, line)) 
		{
			if (line.size() > 7 && line.substr(0, 7) == "include") 
			{
				std::smatch m;
				if (std::regex_match(line, m, std::regex("\\s*include\\s+\"([^\"]+)\"\\s*")))
					shaderSource += loadShader(m[1]);
			}
			else 
			{
				shaderSource += line;
			}
			shaderSource += "\n";
		}
	}
	catch (std::exception e) 
	{
		Debug::fatalError("Loading file (path='" + filePath + "') failed. " + e.what());
	}

	return shaderSource;
}
