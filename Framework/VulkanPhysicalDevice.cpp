#include "VulkanPhysicalDevice.hpp"
#include "VulkanInstance.hpp"


void VulkanPhysicalDevice::Initialize()
{
	/*
	spdlog::info("Enumerating physical devices(video cards)..");

	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(vkInstance.instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		spdlog::critical("Couldn\'t find a physical device!");
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(vkInstance.instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		this->device = device;
		break;
	}

	spdlog::info("Found {0} device(s) selecting this or first device found!", deviceCount);

	*/
	
}



uint32_t VulkanPhysicalDevice::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(device, &memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	throw std::runtime_error("failed to find suitable memory type!");
}