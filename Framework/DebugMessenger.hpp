#pragma once
#include <vulkan/vulkan.hpp>
#include "Configuration.hpp"
#include "VulkanInstance.hpp"
#include "debughelpers.hpp"

class VulkanDebugMessenger
{
public:
	void Initialize();
private:
	// Debugging
	VkDebugUtilsMessengerEXT debugMessenger;
};