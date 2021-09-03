#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <optional>
#include "spdlog/spdlog.h"

#define WINDOW_W	800
#define WINDOW_H	640

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	bool isComplete() {
		return graphicsFamily.has_value();
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

private:

	const char* name;

	void initializeGLFW();

	// Helper functions to decide if physical device is suitable for the application
	// And to find queue families.
	bool isDeviceSuitable(VkPhysicalDevice device);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	// Vulkan
	void createVulkanInstance();
	void enumerateVulkanExtensions();
	void enumeratePhysicalDevices();

	// GlFW window
	GLFWwindow* window;

	// Vulkan instance
	VkInstance instance;

	// Physical & Logical devices @todo(rename to physicalDevice & logicalDevice)
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice = VK_NULL_HANDLE;

	// Queues
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	// Surface(s)
	VkSurfaceKHR surface;
};

