#pragma once
#include "ValidationLayer.hpp"
#include "DebugMessenger.hpp"
#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"
#include "CommandPool.hpp"
#include "VulkanSurface.hpp"

class Vulkan
{

public:

	Vulkan();
	~Vulkan();
	void Initialize();

private:

	// Debug messenger
	VulkanDebugMessenger vulkanDebugMessenger;

	// Physical & Logical devices
	PhysicalDevice physicalDevice = PhysicalDevice();
	LogicalDevice logicalDevice = LogicalDevice();

	// Queues
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Commands
	CommandPool commandPool;

	// Surface
	VulkanSurface surface;

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