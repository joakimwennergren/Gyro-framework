#pragma once
#include "ValidationLayer.hpp"
#include "DebugMessenger.hpp"
#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"

class Vulkan
{
public:
	Vulkan();
	~Vulkan();
protected:
private:

	// Debug messenger
	VulkanDebugMessenger vulkanDebugMessenger;

	// Physical & Logical devices
	PhysicalDevice physicalDevice = PhysicalDevice();
	LogicalDevice logicalDevice = LogicalDevice();

	// Queues
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Swap Chain
	VkSwapchainKHR swapChain;

	// Rendering pipeline
	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	// Semaphores
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
};