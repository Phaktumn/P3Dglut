#pragma once
#include <string>
#include <iostream>

namespace IO
{
	inline void printMessage(std::string& message){
		std::cout << "DEBUG: " + message << std::endl;
	}

	inline void printError(std::string& error){
		std::cerr << "ERROR: " + error << std::endl;
	}
}
