#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <cstdio>
#include <glm/ext.hpp>

namespace Debug
{
	template<typename... Args>
	static void info(std::string fmt, Args... args)
	{
		std::fprintf(stdout, (fmt + "\n").c_str(), args...);
	}

	template<typename... Args>
	static void warning(std::string fmt, Args... args)
	{
		std::fprintf(stdout, ("Warning: " + fmt + "\n").c_str(), args...);
	}

	template<typename... Args>
	static void error(std::string fmt, Args... args)
	{
		fprintf(stderr, ("Error: " + fmt + "\n").c_str(), args...);
	}

	template<typename... Args>
	static void fatalError(std::string fmt, Args... args)
	{
		fprintf(stderr, ("Fatal Error: " + fmt + "\n").c_str(), args...);
		exit(EXIT_FAILURE);
	}
};
#endif // DEBUG_H