# Gyro-framework

## What is this?

Gyro is a framework to make 3D visual effects.

It's a collboration between @joakimwennergren and @klorex

## Target
For now the target is windows platform.
https://github.com/alaingalvan/CrossWindow
( cant build a static/dynamic library out of it so fuck it )

## Stepping stones
* [X] ~~Create a win32 basic window~~
* [X] ~~wrap it in c++ classes~~
* [X] ~~strip unnecessary code/features (like the about callback)~~
* [X] Create an opengl context window
* [ ] Bind vulkan to it
* [ ] Decide on what GPU/3D API to use
* https://alain.xyz/blog/comparison-of-modern-graphics-apis

## Resources

### Libraries
* https://www.raylib.com/ - raylib is a simple and easy-to-use library to enjoy videogames programming. 
might be good for inspiration regarding drawing functions etc.
* https://skia.org/ - 2d graphics engine powering firefox/chrome. Alot of inspiration regarding antialiasing and other stuff.

### GPU Contexts/API
* https://www.vulkan.org/
* https://docs.microsoft.com/en-us/windows/win32/direct3d
* https://www.opengl.org/

### Programming C/C++
* https://www.enlyze.com/blog/writing-win32-apps-like-its-2020/part-2/

### Documentation
* https://vulkan.lunarg.com/

### Findings
* Creating a regular old win32 window doesnt cut it. You need to create the window with https://www.glfw.org/. Vulkan on it's own cant do this.
* When a window is created a vulkan instance is then created and bound to the window if i understand correctly.

### Open issues
* [ ] Which 3D file format should we use?
* [ ] Music synchronization. How do we sync our demo with the music?

### Closed issues
* [X] GLM added to the repo - it contains math functions (matrix multiplication etc)
