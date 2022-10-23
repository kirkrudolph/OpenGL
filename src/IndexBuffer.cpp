#include "IndexBuffer.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint))
    GLCALL(glGenBuffers(1,&m_RendererID));                                  // Number of buffers, buffer ID
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));                     // Select buffer
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));      // Load data

}

IndexBuffer::~IndexBuffer()
{
    GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));                                               

}

void IndexBuffer::Unbind() const
{
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));                                               
}
