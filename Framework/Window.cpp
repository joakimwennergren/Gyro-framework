#include "Window.h"

/// <summary>
/// Window constructor.
/// 1. Sets up a GLFW window
/// 2. Creating a vulkan instance.
/// 3. Enumerate vulkan extensions
/// </summary>
/// <param name="name"></param>
Window::Window(const char * name)
{
	this->name = name;

	// GLFW
	this->initializeGLFW();

	// Vulkan
	this->createVulkanInstance();


	if (enableValidationLayers && !checkValidationLayerSupport()) {
		spdlog::critical("Validation layers requested, but not available!");
		return;
	}

	this->enumerateVulkanExtensions();
	this->enumeratePhysicalDevices();
	this->createLogicalDevice();

	spdlog::info("Trying to create a window surface");
	// Create surface to draw on
	if (glfwCreateWindowSurface(this->instance, this->window, nullptr, &this->surface) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create window surface");
		return;
	}

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { 1 , 1 };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkDeviceCreateInfo createInfo = {};
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	vkGetDeviceQueue(this->logicalDevice, 1, 0, &presentQueue);

	spdlog::info("Successfully created a window surface!");

	// SWAP CHAIN

	spdlog::info("Trying to setup swap chain..");

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();
	
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(this->physicalDevice, this->surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(this->physicalDevice, this->surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(this->physicalDevice, this->surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(this->physicalDevice, this->surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(this->physicalDevice, this->surface, &presentModeCount, details.presentModes.data());
	}

	SwapChainSupportDetails swapChainSupport = details;

	VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfoSwapChain{};
	createInfoSwapChain.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfoSwapChain.surface = this->surface;
	createInfoSwapChain.minImageCount = imageCount;
	createInfoSwapChain.imageFormat = surfaceFormat.format;
	createInfoSwapChain.imageColorSpace = surfaceFormat.colorSpace;
	//createInfoSwapChain.imageExtent = extent;
	createInfoSwapChain.imageArrayLayers = 1;
	createInfoSwapChain.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;


	QueueFamilyIndices indicesSC = findQueueFamilies(physicalDevice);
	uint32_t queueFamilyIndices[] = { 1, 1 };

	if (indicesSC.graphicsFamily != indicesSC.presentFamily) {
		createInfoSwapChain.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfoSwapChain.queueFamilyIndexCount = 2;
		createInfoSwapChain.pQueueFamilyIndices = queueFamilyIndices;
	}
	else {
		createInfoSwapChain.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfoSwapChain.queueFamilyIndexCount = 0; // Optional
		createInfoSwapChain.pQueueFamilyIndices = nullptr; // Optional
	}

	createInfoSwapChain.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfoSwapChain.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfoSwapChain.presentMode = presentMode;
	createInfoSwapChain.clipped = VK_TRUE;
	createInfoSwapChain.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(this->logicalDevice, &createInfoSwapChain, nullptr, &this->swapChain) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t setup swap chain");
	}

	spdlog::info("Successfully setup swap chain!");
}

bool Window::checkValidationLayerSupport() {
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	
	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}

		if (!layerFound) {
			return false;
		}
	}

	return true;
}

VkSurfaceFormatKHR  Window::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) 
{
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}


VkPresentModeKHR Window::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Window::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) 
{
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	}
	else {
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		VkExtent2D actualExtent = {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};

		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}
}

void Window::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = debugCallback;
}


Window::~Window()
{
	vkDestroySurfaceKHR(this->instance, this->surface, nullptr);
	vkDestroyDevice(this->logicalDevice, nullptr);
	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(this->instance, this->debugMessenger, nullptr);
	}
	vkDestroyInstance(this->instance, nullptr);
	glfwDestroyWindow(this->window);
	glfwTerminate();
}

void Window::handleEvents()
{
	while (!glfwWindowShouldClose(this->window)) {
		glfwPollEvents();
	}
}

bool Window::isDeviceSuitable(VkPhysicalDevice device) {
	QueueFamilyIndices indices = this->findQueueFamilies(device);

	return indices.isComplete();
}

QueueFamilyIndices Window::findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete()) {
			break;
		}

		i++;
	}

	return indices;
}

void Window::initializeGLFW()
{
	spdlog::info("Trying to create a GLFW Window..");

	// Initialize GLFW lib
	glfwInit();

	// Don't use openGL and don't allow window resizing
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Assign & create the window
	this->window = glfwCreateWindow(
		WINDOW_W,
		WINDOW_H,
		name,
		nullptr, // 1 monitor windowed for now..
		nullptr // don't share context
	);

	if (!this->window)
	{
		spdlog::critical("Couldn\'t create GLFW window");
		return;
	}

	spdlog::info("Successfully Created a GLFW Window!");
}

void Window::enumerateVulkanExtensions()
{
	spdlog::info("Enumerating vulkan extensions..");

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);

	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	for (const auto& extension : extensions) {
		spdlog::info("{0}, version: {1}", extension.extensionName, extension.specVersion);
	}
}

void Window::createVulkanInstance()
{
	spdlog::info("Trying to create a vulkan instance..");

	// Struct containing basic information about the application
	const VkApplicationInfo appInfo{
		VK_STRUCTURE_TYPE_APPLICATION_INFO,
		this->name,
		nullptr,
		VK_MAKE_VERSION(1, 0, 0),
		"Gyro",
		VK_MAKE_VERSION(1, 0, 0),
		VK_API_VERSION_1_0
	};

	// Struct containing information about the vulkan instance
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	auto extensions = getRequiredExtensions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	// Gather extension count and extension names
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;


	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else {
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
	}

	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		spdlog::info("Failed to create a vulkan instance.");
	}

	spdlog::info("Successfully Created a vulkan instance!");
}

std::vector<const char*> Window::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}

void Window::setupDebugMessenger() {
	if (!enableValidationLayers) return;


	VkDebugUtilsMessengerCreateInfoEXT createInfo;
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

VkResult Window::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void Window::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(instance, debugMessenger, pAllocator);
	}
}

void Window::enumeratePhysicalDevices()
{

	spdlog::info("Enumerating physical devices(video cards)..");

	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		spdlog::critical("Couldn\'t find a physical device!");
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

	for (const auto& device : devices) {
		this->physicalDevice = device;
		break;
	}

	spdlog::info("Found {0} device(s)!", deviceCount);
}

void Window::createLogicalDevice()
{
	spdlog::info("Trying to create a logical device");

	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = 1;
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.pQueueCreateInfos = &queueCreateInfo;
	createInfo.queueCreateInfoCount = 1;

	createInfo.pEnabledFeatures = &deviceFeatures;

	createInfo.enabledExtensionCount = 0;

	const bool enableValidationLayers = false;
	if (enableValidationLayers) {
		//createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		//createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(this->physicalDevice, &createInfo, nullptr, &this->logicalDevice) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(this->logicalDevice, 1, 0, &this->graphicsQueue);

	spdlog::info("Successfully created a logical device");

}