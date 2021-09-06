#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"

class PhysicalDevice 
{
public:
	void enumeratePhysicalDevices();
	VkPhysicalDevice device = VK_NULL_HANDLE;
protected:
private:
};