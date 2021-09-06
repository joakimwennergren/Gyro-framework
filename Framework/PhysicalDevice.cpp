#include "PhysicalDevice.hpp"
#include "VulkanInstance.hpp"

void PhysicalDevice::enumeratePhysicalDevices()
{
	
	spdlog::info("Enumerating physical devices(video cards)..");

	uint32_t deviceCount = 0;

	VulkanInstance* vkInstance = vkInstance->getInstance();

	vkEnumeratePhysicalDevices(vkInstance->getVulkanInstance(), &deviceCount, nullptr);

	if (deviceCount == 0) {
		spdlog::critical("Couldn\'t find a physical device!");
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(vkInstance->getVulkanInstance(), &deviceCount, devices.data());

	for (const auto& device : devices) {
		this->device = device;
		break;
	}

	spdlog::info("Found {0} device(s)!", deviceCount);
	
}