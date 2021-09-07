#pragma once

#include <vulkan/vulkan.hpp>
#include "PhysicalDevice.hpp"
#include "LogicalDevice.hpp"
#include "VulkanSurface.hpp"
#include "GLFW.hpp"

class SwapChain
{
public:

	void Initialize(PhysicalDevice physicalDevice, LogicalDevice logicalDevice, VulkanSurface vulkanSurface);

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	SwapChainSupportDetails querySwapChainSupport(PhysicalDevice physicalDevice,  VulkanSurface vulkanSurface);

	VkFormat getSwapChainImageFormat() { return this->swapChainImageFormat; }
	VkExtent2D getSwapChainExtent() { return this->swapChainExtent; }
private:

	VkExtent2D swapChainExtent;
	VkFormat swapChainImageFormat;
	VkSwapchainKHR swapChain;

	VkSurfaceFormatKHR  chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};