#pragma once
#include <exception>

class InvalidFileException :public std::exception
{
public:
	InvalidFileException() {};
	const char* what() const noexcept {
		return "Failed to open file.\n"; 
	}
};