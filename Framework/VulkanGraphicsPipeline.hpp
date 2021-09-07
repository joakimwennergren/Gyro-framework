#pragma once
#include <vulkan/vulkan.hpp>
#include "Swapchain.hpp"
#include "VulkanPipelineLayout.hpp"
#include "RenderPass.hpp"

class VulkanGraphicsPipeline
{
public:
	void Create(LogicalDevice logicalDevice, ShaderModule vertShaderModule, ShaderModule fragShaderModule, SwapChain swapChain, VulkanPipelineLayout pipelineLayout, RenderPass renderPass);
	VkPipeline getPipeline() { return this->graphicsPipeline; }
private:
	VkPipeline graphicsPipeline;
};