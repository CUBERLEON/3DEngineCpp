#pragma once

#include <string>
#include <cstdio>

namespace Debug
{
	template<typename... Args>
	void info(std::string fmt, Args... args)
	{
		std::printf(("INFO: " + fmt + "\n").c_str(), args...);
	}

	template<typename... Args>
	void error(std::string fmt, Args... args)
	{
		fprintf(stderr, ("ERROR: " + fmt + "\n").c_str(), args...);
	}

	template<typename... Args>
	void fatalError(std::string fmt, Args... args)
	{
		fprintf(stderr, ("Fatal ERROR: " + fmt + "\n").c_str(), args...);
		exit(EXIT_FAILURE);
	}
};