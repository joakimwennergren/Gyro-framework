#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "spdlog/spdlog.h"
#include "Configuration.hpp"


class GLFW {
	static GLFW* instance;

	// Private constructor so that no objects can be created.
	GLFW() {

		spdlog::info("Trying to initialize a new GLFW window..");

		// Initialize GLFW lib
		glfwInit();

		// Don't use openGL and don't allow window resizing
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Assign & create the window
		window = glfwCreateWindow(
			WINDOW_W,
			WINDOW_H,
			APPLICATION_NAME,
			nullptr, // 1 monitor windowed for now..
			nullptr // don't share context
		);

		if (!window)
		{
			spdlog::critical("Couldn\'t create GLFW window");
			return;
		}

		spdlog::info("Successfully initialized a GLFW window!");

	}

public:
	static GLFW* getInstance() {
		if (!instance)
			instance = new GLFW;
		return instance;
	}

	GLFWwindow* getWindow() {
		return this->window;
	}

private:
	GLFWwindow* window;

};
