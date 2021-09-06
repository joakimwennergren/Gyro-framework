#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"

class CommandPool
{
public:
	CommandPool();
	~CommandPool();
	void Initialize(LogicalDevice logicalDevice);
protected:
private:
	VkCommandPool commandPool;
};