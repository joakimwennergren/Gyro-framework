#include "ShaderModule.hpp"


void ShaderModule::create(LogicalDevice logicalDevice, const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(logicalDevice.device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t!");
	}

}