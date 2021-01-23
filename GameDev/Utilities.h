#pragma once

class Utilities
{
public:
	static inline bool IsInteger(const std::string& string)
	{
		if (string.empty() ||
			((!isdigit(string[0])) && (string[0] != '-') && (string[0] != '+')))
			return false;

		char* p;
		strtol(string.c_str(), &p, 10);
		return(*p == 0);
	}
};