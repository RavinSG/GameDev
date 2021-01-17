#include "Helper.h"

bool Helper::FileExists(const std::string& fileName)
{
    return std::filesystem::exists(fileName);
}

void Helper::PrintFiles(const std::string& dirName)
{
    for (const auto& entry : fs::directory_iterator(dirName))
        std::cout << entry.path() << std::endl;
}
