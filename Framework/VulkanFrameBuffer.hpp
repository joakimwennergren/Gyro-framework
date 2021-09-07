#pragma once
#include <vulkan/vulkan.hpp>
#include "spdlog/spdlog.h"
#include "VulkanLogicalDevice.hpp"
#include "Swapchain.hpp"
#include "RenderPass.hpp"
#include "VulkanImageView.hpp"


class VulkanFrameBuffer
{
public:
	void Create(VulkanLogicalDevice logicalDevice, SwapChain swapChain, RenderPass renderPass, VulkanImageView imageView);
	VkFramebuffer getBuffer() { return this->buffer; }
private:
	VkFramebuffer buffer;
};