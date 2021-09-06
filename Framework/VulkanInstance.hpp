#pragma once
#include <vulkan/vulkan.hpp>
#include "Configuration.hpp"
#include "spdlog/spdlog.h"
#include "VulkanExtension.hpp"
#include "DebugCallbacks.hpp"

class VulkanInstance {
    static VulkanInstance* instance;
    
    VkInstance vkInstance;
    
    // Private constructor so that no objects can be created.
    VulkanInstance() {

		spdlog::info("Trying to initialize a new vulkan instance..");

		// Struct containing basic information about the application
		const VkApplicationInfo appInfo{
			VK_STRUCTURE_TYPE_APPLICATION_INFO,
			nullptr,
			APPLICATION_NAME,
			VK_MAKE_VERSION(1, 0, 0),
			"Gyro",
			VK_MAKE_VERSION(1, 0, 0),
			VK_API_VERSION_1_0
		};

		// Struct containing information about the vulkan instance
		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

#if ENABLE_VALIDATION_LAYERS == true
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
		VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
		debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		debugCreateInfo.pfnUserCallback = DebugCallbacks::debugCallback;
		debugCreateInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
#else
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
#endif
		
		auto extensions = VulkanExtension::getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		
		if (vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS) {
			spdlog::info("Failed to create a vulkan instance.");
		}

		spdlog::info("Successfully Created a vulkan instance!");

    }

public:
    static VulkanInstance* getInstance() {
        if (!instance)
            instance = new VulkanInstance;
        return instance;
    }

    VkInstance getVulkanInstance() {
        return this->vkInstance;
    }

};

