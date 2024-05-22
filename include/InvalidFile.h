#pragma once

class InvalidFile :public std::exception
{
public:
	InvalidFile() {};
	const char* what() const noexcept {
		return "Failed to open file: Invalid path.\n"; //נדפיס שגיאה יפה יותר
	}
};