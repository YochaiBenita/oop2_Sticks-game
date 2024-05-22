#pragma once
#include <exception>


class InvalidContentFile :public std::exception
{
public:
	InvalidContentFile() {};
	const char* what() const noexcept {
		return "The content is invalid\n"; //נדפיס שגיאה יפה יותר
	}
};