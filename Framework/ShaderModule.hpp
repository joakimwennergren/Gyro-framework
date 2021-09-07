#include <vulkan/vulkan.hpp>
#include "LogicalDevice.hpp"
class ShaderModule 
{
	public:
		void create(LogicalDevice logicalDevice, const std::vector<char>& code);
		VkShaderModule getShaderModule() { return this->shaderModule; }
	private:
		VkShaderModule shaderModule;
};