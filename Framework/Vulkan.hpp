#pragma once
#include "ValidationLayer.hpp"
#include "DebugMessenger.hpp"
#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"
#include "CommandPool.hpp"
#include "CommandBuffer.hpp"
#include "VulkanSurface.hpp"
#include "VulkanPipelineLayout.hpp"
#include "VulkanSemaphore.hpp"
#include "Swapchain.hpp"
#include "RenderPass.hpp"

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
	std::vector<Gyro::Vulkan::Commands::CommandBuffer> commandBuffers;

	// Surface
	VulkanSurface surface;

	// Swap Chain
	SwapChain swapChain;

	// Rendering pipeline
	RenderPass renderPass;
	VulkanPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	// Semaphores
	VulkanSemaphore imageAvailableSemaphore;
	VulkanSemaphore renderFinishedSemaphore;

};