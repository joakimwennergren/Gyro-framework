// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Window.hpp"
#include <iostream>

int main()
{
    Window* window = new Window();
    
    window->loop();

    delete window;

    return 0;
}
