#pragma once
#include <string>
#define String std::string

#ifdef WIN32
// Windows
#endif
#ifdef __linux__
// Linux
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif
#ifdef __APPLE__
// Mac

#endif
