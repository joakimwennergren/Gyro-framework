#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"

class LogicalDevice
{
public:
	LogicalDevice(VkPhysicalDevice physicalDevice);
	VkDevice instance;
protected:

private:

};