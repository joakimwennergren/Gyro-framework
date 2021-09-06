#include "DebugCallbacks.hpp"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallbacks::debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {

	spdlog::info(pCallbackData->pMessage);

	return VK_FALSE;
}