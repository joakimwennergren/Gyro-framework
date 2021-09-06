#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include "Configuration.hpp"

class GLFW
{
public:
	GLFW();
	~GLFW();
	GLFWwindow* window;
private:

};