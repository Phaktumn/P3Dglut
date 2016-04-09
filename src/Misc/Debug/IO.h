#pragma once
#include <string>
#include <iostream>

namespace IO
{
	inline void printMessage(const std::string& message){
		std::cout << "DEBUG: " + message << std::endl;
	}

	inline void printError(const std::string& error){
		std::cerr << "ERROR: " + error << std::endl;
	}
}
