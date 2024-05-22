#pragma once
#include <exception>

class InvalidFile :public std::exception
{
public:
	InvalidFile() {};
	const char* what() const noexcept {
		return "Failed to open file.\n"; //נדפיס שגיאה יפה יותר
	}
};