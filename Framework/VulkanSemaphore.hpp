#pragma once

#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"

class VulkanSemaphore
{
public:
	void create(LogicalDevice logicalDevice);
	VkSemaphore getSemaphore() { return this->semaphore; }
private:
	VkSemaphore semaphore;
};