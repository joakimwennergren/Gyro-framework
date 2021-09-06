#pragma once
#include <vector>
#include <GLFW/glfw3.h>
#include <set>
#include <vulkan/vulkan.hpp>
#include "Configuration.hpp"
#include "PhysicalDevice.hpp"

class VulkanExtension
{
public:
	static std::vector<const char*> getRequiredExtensions();
	static bool checkDeviceExtensionSupport(PhysicalDevice physicalDevice);
};