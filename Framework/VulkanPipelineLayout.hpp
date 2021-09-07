#pragma once
#include <vulkan/vulkan.hpp>
#include "ShaderModule.hpp"
#include "LogicalDevice.hpp"
#include "Swapchain.hpp"

class VulkanPipelineLayout
{
public:
	void Create(LogicalDevice logicalDevice, ShaderModule vertShaderModule, ShaderModule fragShaderModule, SwapChain swapChain);
	VkPipelineLayout getLayout() { return this->pipelineLayout;  }
private:
	VkPipelineLayout pipelineLayout;
};