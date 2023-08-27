#pragma once

namespace Yumi
{
    class VertexBuffer;
    class IndexBuffer;
    
    class VertexArray
    {
    public:
        static Shared<VertexArray> Create();
        
        VertexArray();
        ~VertexArray();
        
        void Bind() const;
        void Unbind() const;
        
        void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer);

        const DynamicArray<Shared<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
        const Shared<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
        
    private:
        uint32_t m_VertexArrayId;
        DynamicArray<Shared<VertexBuffer>> m_VertexBuffers;
        Shared<IndexBuffer> m_IndexBuffer;
    };
}
