#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "VulkanPhysicalDevice.hpp"
#include "Configuration.hpp"

class VulkanLogicalDevice
{
public:
	void Initialize(VulkanPhysicalDevice physicalDevice);
	VkDevice device;
protected:

private:

};