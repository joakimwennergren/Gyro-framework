#include "VulkanImageView.hpp"

void VulkanImageView::Create(LogicalDevice logicalDevice, VulkanTexture texture, SwapChain swapchain)
{
	VkImageViewCreateInfo createInfoImageView{};
	createInfoImageView.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfoImageView.image = texture.getTexture();
	createInfoImageView.viewType = VK_IMAGE_VIEW_TYPE_2D;
	createInfoImageView.format = swapchain.getSwapChainImageFormat();
	createInfoImageView.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfoImageView.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfoImageView.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfoImageView.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	createInfoImageView.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	createInfoImageView.subresourceRange.baseMipLevel = 0;
	createInfoImageView.subresourceRange.levelCount = 1;
	createInfoImageView.subresourceRange.baseArrayLayer = 0;
	createInfoImageView.subresourceRange.layerCount = 1;
	
	if (vkCreateImageView(logicalDevice.device, &createInfoImageView, nullptr, &imageView) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create image views!");
	}
}