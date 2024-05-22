#pragma once
#include <exception>


class InvalidContentFileException :public std::exception
{
public:
	InvalidContentFileException() {};
	const char* what() const noexcept {
		return "The content is invalid\n"; //נדפיס שגיאה יפה יותר
	}
};