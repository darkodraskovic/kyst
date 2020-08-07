#pragma once

#include <string>
#include <fstream>
#include <iostream>

class Includer
{
public:
    static std::string Include(std::string path, std::string includeIndentifier = "#include");

private:
    static void GetFilePath(const std::string & fullPath, std::string & pathWithoutFileName);
};
