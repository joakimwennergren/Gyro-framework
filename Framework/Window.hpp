#pragma once

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <cstdint> 
#include <optional>
#include <set>
#include <algorithm> 
#include <fstream>
#include <tiny_obj_loader.h>

#include "spdlog/spdlog.h"
#include "LogicalDevice.hpp"
#include "PhysicalDevice.hpp"
#include "stb_image.h"
#include "Configuration.hpp"
#include "logicalDevice.hpp"
#include "ValidationLayer.hpp"
#include "File.hpp"
#include "VulkanInstance.hpp"
#include "DebugHelpers.hpp"
#include "DebugCallbacks.hpp"
#include "DebugMessenger.hpp"
#include "GLFW.hpp"

struct Vertex {
	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 texCoord;


		static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


class Window
{
public:

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createTextureImage();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	// Constructor
	Window();

	// Destructor
	~Window();

	void loop();


private:

	// GlFW window
	GLFW glfw;


	// Helper functions to decide if physical device is suitable for the application
	// And to find queue families.
	bool isDeviceSuitable(VkPhysicalDevice device);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);



	std::vector<VkFramebuffer> swapChainFramebuffers;


	void createRenderPass();

	void createFramebuffers();

	VkCommandPool commandPool;

	std::vector<VkCommandBuffer> commandBuffers;

	VkShaderModule createShaderModule(const std::vector<char>& code);
	void createGraphicsPipeline();

	void createCommandPool();
	void createCommandBuffers();


	void createSemaphores();

	void drawFrame();

	void initVulkan();

	void createSurface();

	void createImageViews();

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	void createSwapChain();

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);


	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

};



