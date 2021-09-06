#include "CommandPool.hpp"

CommandPool::CommandPool()
{

}
CommandPool::~CommandPool()
{

}

void CommandPool::Initialize(LogicalDevice logicalDevice)
{
	if (logicalDevice.device == nullptr)
	{
		spdlog::critical("Trying to create commandpool with nullptr logicalDevice!");
		return;
	}

	spdlog::info("Trying to initialize command pool..");

	//QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice.device);

	VkCommandPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = 0;
	poolInfo.flags = 0; // Optional
	
	if (vkCreateCommandPool(logicalDevice.device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create commandpool.");
	}

	spdlog::info("Successfully initialized command pool!");
	
}