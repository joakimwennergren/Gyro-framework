// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Framework.hpp"
#include <iostream>

int main()
{
    Window* window = new Window("Vulkan evaluation");
    
    window->loop();

    delete window;

    return 0;
}
