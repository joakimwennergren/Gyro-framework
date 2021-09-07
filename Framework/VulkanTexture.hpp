#pragma once
#include <vulkan/vulkan.hpp>
#include "stb_image.h"
#include "LogicalDevice.hpp"
#include "VulkanUtility.hpp"

class VulkanTexture
{
public:
	void Create(LogicalDevice logicalDevice, PhysicalDevice physicalDevice, const char* path);
	VkImage getTexture() { return this->texture; };
private:
	VkImage texture;
	VkDeviceMemory textureImageMemory;
};