#include "LogicalDevice.hpp"

LogicalDevice::LogicalDevice(VkPhysicalDevice physicalDevice)
{
	// Sanity check
	if (physicalDevice ==  VK_NULL_HANDLE)
	{
		spdlog::critical("Trying to initialize a logical device with an null handle physical device!");
		return;
	}

	spdlog::info("Trying to initialize a logical device..");

	const float queuePriority = 1.0f;

	// Queues
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = 0;
	queueCreateInfo.queueCount = 1;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	// Device Features
	VkPhysicalDeviceFeatures deviceFeatures{};

	/*
	// Create information
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	// Should we use validation layers or not
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	// Create the logical device
	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &instance) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t initialize a logical device!");
		return;
	}
	*/

	spdlog::info("Successfully initialized a logical device");
}