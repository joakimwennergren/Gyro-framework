#include "DebugMessenger.hpp"


void VulkanDebugMessenger::Initialize() {

#if ENABLE_VALIDATION_LAYERS == true

	VulkanInstance* vkInstance = vkInstance->getInstance();

	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = DebugCallbacks::debugCallback;

	if (DebugHelpers::CreateDebugUtilsMessengerEXT(vkInstance->getVulkanInstance(), &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		spdlog::critical("Failed to create debug utils messenger!");
	}

#else
	return;
#endif
}