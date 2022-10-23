#include "VertexBuffer.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCALL(glGenBuffers(1,&m_RendererID));                                  // Number of buffers, buffer ID
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER,m_RendererID));                     // Select buffer
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));      // Load data

}

VertexBuffer::~VertexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));                                               

}

void VertexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));                                               
}
