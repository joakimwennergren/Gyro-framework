#pragma once

#include <vulkan/vulkan.hpp>
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"
#include "VulkanTexture.hpp"
#include "Swapchain.hpp"
#include "spdlog/spdlog.h"

class VulkanImageView
{
public:
	void Create(LogicalDevice logicalDevice, VulkanTexture texture, SwapChain swapchain);
private:
	VkImageView imageView;
};