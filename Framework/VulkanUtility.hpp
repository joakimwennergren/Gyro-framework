#pragma once
#include <vulkan/vulkan.hpp>
#include "LogicalDevice.hpp"
#include "PhysicalDevice.hpp"

class VulkanUtility
{
public:
    static void createBuffer(LogicalDevice logicalDevice, PhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
};