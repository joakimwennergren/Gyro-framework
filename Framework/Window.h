#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <optional>
#include "spdlog/spdlog.h"
#include <set>
#include <cstdint> // Necessary for UINT32_MAX
#include <algorithm> // Necessary for std::min/std::max

#define WINDOW_W	800
#define WINDOW_H	640

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};

class Window
{
public:

	// Constructor
	Window(const char * name);

	// Destructor
	~Window();

	// Handle basic events such as window resizing, closing the window etc..
	void handleEvents();

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData) {

		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}

private:

	const char* name;

	void initializeGLFW();

	// Helper functions to decide if physical device is suitable for the application
	// And to find queue families.
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);


	bool checkValidationLayerSupport();

	// Vulkan
	void createVulkanInstance();
	void enumerateVulkanExtensions();
	void enumeratePhysicalDevices();
	void createLogicalDevice();

	// GlFW window
	GLFWwindow* window;

	// Vulkan instance
	VkInstance instance;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

	VkResult CreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pDebugMessenger
	);

	void setupDebugMessenger();

	void DestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT debugMessenger,
		const VkAllocationCallbacks* pAllocator
	);

	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	std::vector<const char*> getRequiredExtensions();

	// Physical & Logical devices @todo(rename to physicalDevice & logicalDevice)
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice = VK_NULL_HANDLE;

	// Queues
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Surface(s)
	VkSurfaceKHR surface;

	// Swap Chain
	VkSwapchainKHR swapChain;

	// Debugging
	VkDebugUtilsMessengerEXT debugMessenger;
};

