#include "LogicalDevice.hpp"

LogicalDevice::LogicalDevice()
{

}

LogicalDevice:: ~LogicalDevice()
{

}


void LogicalDevice::Initialize(PhysicalDevice physicalDevice)
{

	// Sanity check
	if (physicalDevice.device == VK_NULL_HANDLE)
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

	// Vulkan device extensions
	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	// Create information
	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	// Should we use validation layers or not
#if ENABLE_VALIDATION_LAYERS == true
	createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	createInfo.ppEnabledLayerNames = validationLayers.data();
#else
	createInfo.enabledLayerCount = 0;
#endif

	// Create the logical device
	if (vkCreateDevice(physicalDevice.device, &createInfo, nullptr, &device) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t initialize a logical device!");
		return;
	}

	spdlog::info("Successfully initialized a logical device");
}