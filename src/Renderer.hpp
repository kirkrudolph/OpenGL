#pragma once

#include "glew.h"

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

// Macros
#define ASSERT(x) if (!(x)) __builtin_debugtrap();
#define GLCALL(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Functions
void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer{
    public:
        void Clear() const;
        void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};