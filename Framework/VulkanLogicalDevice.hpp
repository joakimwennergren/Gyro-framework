#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "PhysicalDevice.hpp"
#include "Configuration.hpp"

class LogicalDevice
{
public:
	void Initialize(PhysicalDevice physicalDevice);
	VkDevice device;
protected:

private:

};