#pragma once

// Application
#define APPLICATION_NAME	"DEMOSCENE"
#define WINDOW_W	800
#define WINDOW_H	600

// Validation layers
#define ENABLE_VALIDATION_LAYERS	true
const std::vector<const char*> validationLayers = {
	"VK_LAYER_KHRONOS_validation"
};

// Vulkan device extensions
const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};