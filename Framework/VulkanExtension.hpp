#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include "Configuration.hpp"

class VulkanExtension
{
public:
	static std::vector<const char*> getRequiredExtensions();
};