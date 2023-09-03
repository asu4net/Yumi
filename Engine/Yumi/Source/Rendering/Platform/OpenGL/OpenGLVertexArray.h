#pragma once
#include "Rendering/VertexArray.h"

namespace Yumi
{
    class VertexBuffer;
    class IndexBuffer;
    
    class OpenGLVertexArray : public VertexArray
    {
    public:        
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        
        void Bind() const override;
        void Unbind() const override;
        
        void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) override;
        void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) override;

        const DynamicArray<Shared<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        const Shared<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
        
    private:
        uint32_t m_VertexArrayId;
        DynamicArray<Shared<VertexBuffer>> m_VertexBuffers;
        Shared<IndexBuffer> m_IndexBuffer;
    };
}
