#include "VertexBuffer.h"
#include <glad/glad.h>

namespace Yumi
{
    Shared<VertexBuffer> VertexBuffer::Create(const void* vertices, const uint32_t size)
    {
        return std::make_shared<VertexBuffer>(vertices, size);
    }

    Shared<VertexBuffer> VertexBuffer::Create(const uint32_t size)
    {
        return std::make_shared<VertexBuffer>(size);
    }

    VertexBuffer::VertexBuffer(const void* vertices, const uint32_t size)
        : m_BufferId(0)
    {
        glCreateBuffers(1, &m_BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(const uint32_t size)
    {
        glCreateBuffers(1, &m_BufferId);
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferId);
    }

    void VertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    }

    void VertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, const uint32_t size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::SetLayout(const BufferLayout& bufferLayout)
    {
        m_Layout = bufferLayout;
    }
}