// 
// This file contains some platform specific dependencies
// that are included when needed and some general construct
// that I personally like to use.
// 
// The external libraries headers are also loaded here.
//
#pragma once
#ifdef WIN32 // We're on windows

#elif __linux__ // We're on linux

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#elif __APPLE__ // Macintosh

#else // We don't know what we're on... Maybe pot?
#error "Unknown platform, none of the compiler flags: 'WIN32', '__linux__' or '__APPLE__' were set."
#endif

