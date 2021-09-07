#pragma once
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <set>
#include "spdlog/spdlog.h"
#include "VulkanInstance.hpp"
#include "GLFW.hpp"

class VulkanSurface
{
public:
	void create();
	VkSurfaceKHR surface;
private:

};