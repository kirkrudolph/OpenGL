#pragma once

#include "glew.h"

// Macros
#define ASSERT(x) if (!(x)) __builtin_debugtrap();
#define GLCALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Functions
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);