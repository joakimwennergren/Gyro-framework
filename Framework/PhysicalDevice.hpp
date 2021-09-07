#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"

class PhysicalDevice 
{
public:
	void Initialize();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VkPhysicalDevice device = VK_NULL_HANDLE;
protected:
private:
};