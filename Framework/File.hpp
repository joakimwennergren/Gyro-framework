#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"

class File
{
public:
		static std::vector<char> readFile(const std::string& filename);
};

