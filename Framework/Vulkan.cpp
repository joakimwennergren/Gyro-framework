#include "Vulkan.hpp"


Vulkan::Vulkan()
{

}


Vulkan::~Vulkan()
{
	/*
	for (auto imageView : swapChainImageViews) {
		vkDestroyImageView(this->logicalDevice.device, imageView, nullptr);
	}

	vkDestroyPipelineLayout(logicalDevice.device, pipelineLayout, nullptr);
	vkDestroyPipeline(logicalDevice.device, graphicsPipeline, nullptr);

	vkDestroyRenderPass(logicalDevice.device, renderPass, nullptr);

	for (auto framebuffer : swapChainFramebuffers) {
		vkDestroyFramebuffer(logicalDevice.device, framebuffer, nullptr);
	}

	vkDestroyCommandPool(logicalDevice.device, commandPool, nullptr);

	vkDestroyShaderModule(this->logicalDevice.device, fragShaderModule, nullptr);
	vkDestroyShaderModule(this->logicalDevice.device, vertShaderModule, nullptr);

	vkDestroySemaphore(logicalDevice.device, renderFinishedSemaphore, nullptr);
	vkDestroySemaphore(logicalDevice.device, imageAvailableSemaphore, nullptr);
	/*
	vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
	vkDestroyDevice(this->logicalDevice.device, nullptr);
	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(this->instance, this->debugMessenger, nullptr);
	}


	vkDestroyInstance(this->instance, nullptr);
	*/
}

void Vulkan::Initialize()
{

#if ENABLE_VALIDATION_LAYERS

	// Set up validation layers & debugging..
	if (ValidationLayer::checkValidationLayerSupport()) {
		vulkanDebugMessenger.Initialize();
	}
	else {
		spdlog::critical("Validation layers & debugging requested, but wasn't supported. Skipping..");
	}

#endif

	physicalDevice.Initialize();
	logicalDevice.Initialize(physicalDevice);

	commandPool.Initialize(logicalDevice);
}