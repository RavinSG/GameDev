#pragma once

#include <iostream>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class Helper
{
public:
	bool FileExists(const std::string& fileName);
	void PrintFiles(const std::string& dirName);
};

