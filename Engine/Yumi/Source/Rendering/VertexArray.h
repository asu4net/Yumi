#pragma once
#include "Rendering/GraphicsAPI.h"

namespace Yumi
{
    class VertexBuffer;
    class IndexBuffer;

    class VertexArray
    {
    public:
        static Shared<VertexArray> Create(GraphicsAPI api);

        virtual ~VertexArray() = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Shared<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer) = 0;

        virtual const DynamicArray<Shared<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Shared<IndexBuffer>& GetIndexBuffer() const = 0;
    };
}
