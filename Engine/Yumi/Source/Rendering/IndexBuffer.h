﻿#pragma once
#include "GraphicsAPI.h"

namespace Yumi
{
    class IndexBuffer
    {
    public:
        static Shared<IndexBuffer> Create(GraphicsAPI api, const uint32_t* indices, uint32_t count);

        virtual ~IndexBuffer() = 0;
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetCount() const = 0;
    };
}
