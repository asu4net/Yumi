#pragma once


namespace Yumi
{
    class FrameBuffer
    {
    public:
        struct Configuration
        {
            uint32_t Width{1280}, Height{720};
        };
        
        static SharedPtr<FrameBuffer> Create(GraphicsAPI api, const Configuration& configuration);
        
        virtual ~FrameBuffer() = 0;

        virtual uint32_t GetColorAttachment() const = 0;
        
        virtual void Invalidate() = 0;
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual void Resize(const Vector2& size) = 0;
    };
}