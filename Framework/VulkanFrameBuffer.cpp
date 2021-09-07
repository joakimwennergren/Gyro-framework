#include "VulkanFrameBuffer.hpp"

void VulkanFrameBuffer::Create(VulkanLogicalDevice logicalDevice, SwapChain swapChain, RenderPass renderPass, VulkanImageView imageView)
{

	VkImageView attachment[] = {
		imageView.getImageView()
	};

	VkFramebufferCreateInfo framebufferInfo{};
	framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferInfo.renderPass = renderPass.renderPass;
	framebufferInfo.attachmentCount = 1;
	framebufferInfo.pAttachments = attachment;
	framebufferInfo.width = swapChain.getSwapChainExtent().width;
	framebufferInfo.height = swapChain.getSwapChainExtent().height;
	framebufferInfo.layers = 1;

	if (vkCreateFramebuffer(logicalDevice.device, &framebufferInfo, nullptr, &buffer) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t!");
	}
}