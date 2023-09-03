#pragma once
#include "Rendering/FrameBuffer.h"

namespace Yumi
{
    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const Configuration& configuration);
        ~OpenGLFrameBuffer() override;

        uint32_t GetColorAttachment() const override { return m_ColorAttachment; }

        void Invalidate() override;
        void Bind() const override;
        void Unbind() const override;
        void Resize(const Vector2& size) override;

    private:
        uint32_t m_FrameBufferId = 0;
        uint32_t m_ColorAttachment = 0;
        uint32_t m_DepthAttachment = 0;
        Configuration m_Configuration;
    };
}