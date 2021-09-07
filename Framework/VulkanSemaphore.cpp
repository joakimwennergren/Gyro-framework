#include "VulkanSemaphore.hpp"

void VulkanSemaphore::create(LogicalDevice logicalDevice)
{
	VkSemaphoreCreateInfo semaphoreInfo{};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(logicalDevice.device, &semaphoreInfo, nullptr, &semaphore) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create semaphore!");
	}
}