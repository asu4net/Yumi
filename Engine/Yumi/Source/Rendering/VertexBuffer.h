#pragma once
#include "Rendering/BufferLayout.h"
#include "Rendering/GraphicsAPI.h"

namespace Yumi
{
    class VertexBuffer
    {
    public:
        static Shared<VertexBuffer> Create(GraphicsAPI api, const void* vertices, uint32_t size);
        static Shared<VertexBuffer> Create(GraphicsAPI api, uint32_t size);

        virtual ~VertexBuffer() = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void SetData(const void* data, uint32_t size) const = 0;

        virtual void SetLayout(const BufferLayout& bufferLayout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;
    };
}