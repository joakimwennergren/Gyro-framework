#pragma once

#include <vulkan/vulkan.hpp>

class CommandBuffer
{
public:
	void Create();
private:
	VkCommandBuffer buffer;
};