﻿#pragma once

#include "BufferLayout.h"

namespace Yumi
{
    class VertexBuffer
    {
    public:
        static Shared<VertexBuffer> Create(const void* vertices, uint32_t size);
        static Shared<VertexBuffer> Create(uint32_t size);
        
        VertexBuffer(const void* vertices, uint32_t size);
        VertexBuffer(uint32_t size);
        ~VertexBuffer();
        
        void Bind() const;
        void Unbind() const;
        void SetData(const void* data, uint32_t size) const;
        
        void SetLayout(const BufferLayout& bufferLayout);
        const BufferLayout& GetLayout() const { return m_Layout; }
    
    private:
        uint32_t m_BufferId{};
        BufferLayout m_Layout;
    };
}