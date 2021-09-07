#include "VulkanSurface.hpp"

void VulkanSurface::create()
{
	spdlog::info("Trying to create a window surface");

	VulkanInstance* vkInstance = vkInstance->getInstance();
	GLFW* glfw = glfw->getInstance();


	// Create surface to draw on
	if (glfwCreateWindowSurface(vkInstance->getVulkanInstance(), glfw->getWindow(), nullptr, &this->surface) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create window surface");
		return;
	}

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { 0 , 0 };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = 0;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceCreateInfo createInfo = {};
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();


	spdlog::info("Successfully created a window surface!");
	
}
