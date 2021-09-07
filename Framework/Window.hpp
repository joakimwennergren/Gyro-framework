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
#include "stb_image.h"
#include "Configuration.hpp"
#include "GLFW.hpp"
#include "Vulkan.hpp"

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

	Window();

	~Window();

	void loop();


private:

#if USE_VULKAN == true
	// Vulkan API
	Vulkan vulkan;
#endif

	// Helper functions to decide if physical device is suitable for the application
	// And to find queue families.
	bool isDeviceSuitable(VkPhysicalDevice device);

	std::vector<VkFramebuffer> swapChainFramebuffers;

	void createRenderPass();

	void createFramebuffers();

	void createGraphicsPipeline();

	void createCommandPool();
	void createCommandBuffers();


	void createSemaphores();

	void drawFrame();

	void createSurface();

	void createImageViews();

	//SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);


	VkCommandBuffer beginSingleTimeCommands();
	void endSingleTimeCommands(VkCommandBuffer commandBuffer);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);

};



