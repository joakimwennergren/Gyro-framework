#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "PhysicalDevice.hpp"

class LogicalDevice
{
public:
	LogicalDevice();
	~LogicalDevice();

	void Initialize(PhysicalDevice physicalDevice);
	VkDevice device;
protected:

private:

};