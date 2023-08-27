﻿#pragma once

namespace Yumi
{
    class FrameBuffer
    {
    public:
        struct Configuration
        {
            uint32_t Width{1280}, Height{720};
        };
        
        FrameBuffer(const Configuration& configuration);
        ~FrameBuffer();

        uint32_t GetColorAttachment() const { return m_ColorAttachment; }
        
        void Invalidate();
        void Bind();
        void Unbind();
        void Resize(const Vector2& size);
        
    private:
        uint32_t m_FrameBufferId = 0;
        uint32_t m_ColorAttachment = 0;
        uint32_t m_DepthAttachment = 0;
        Configuration m_Configuration;
    };
}