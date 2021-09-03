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

	this->initializeGLFW();

	this->createVulkanInstance();

	this->enumerateVulkanExtensions();

	this->enumeratePhysicalDevices();

	/*
	// ** TEMP CREATE A LOGICAL DEVICE

	QueueFamilyIndices indices = this->findQueueFamilies(physicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	float queuePriority = 1.0f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfoLogicalDevice{};
	createInfoLogicalDevice.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfoLogicalDevice.pQueueCreateInfos = &queueCreateInfo;
	createInfoLogicalDevice.queueCreateInfoCount = 1;

	createInfoLogicalDevice.pEnabledFeatures = &deviceFeatures;


	createInfo.enabledExtensionCount = 0;

	bool enableValidationLayers = false;

	if (enableValidationLayers) {
		//createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		//createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else {
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(physicalDevice, &createInfoLogicalDevice, nullptr, &device) != VK_SUCCESS) {
		printf("Failed to create logical device");
	}

	vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);


	// ** TEMP SURFACE

	if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
		printf("Failed to create surface");
	}

	*/
}

Window::~Window()
{
	//vkDestroySurfaceKHR(instance, surface, nullptr);
	//vkDestroyDevice(this->device, nullptr);
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

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
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

	// Gather extension count and extension names
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	// Enable layer count?
	createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &this->instance) != VK_SUCCESS) {
		spdlog::critical("Couldn\'t create a vulkan instance!");
		return;
	}

	spdlog::info("Successfully Created a vulkan instance!");
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

	spdlog::info("Found {0} device(s)!", deviceCount);
}