// Framework.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Window.h"
#include <iostream>

int main()
{
    Window* window = new Window();
    
    window->handleEvents();

    delete window;

    return 0;
}
