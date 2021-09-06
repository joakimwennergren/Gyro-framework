#include "GLFW.hpp"

GLFW::GLFW()
{
	spdlog::info("Trying to create a GLFW Window..");

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

	spdlog::info("Successfully Created a GLFW Window!");
}

GLFW::~GLFW()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}