#ifndef GLSL_VARIABLE_H
#define GLSL_VARIABLE_H

#include <string>

struct GLSLvariable
{
public:
	std::string type;
	std::string name;

	GLSLvariable(const std::string& type, const std::string& name) : type(type), name(name) {}
};
#endif // GLSL_VARIABLE_H