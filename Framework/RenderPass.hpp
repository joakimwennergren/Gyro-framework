#pragma once
#include <vulkan/vulkan.hpp>
#include "Swapchain.hpp"

class RenderPass
{
public:
	void create(LogicalDevice logicalDevice, SwapChain swapChain);
	VkRenderPass renderPass;
private:
};