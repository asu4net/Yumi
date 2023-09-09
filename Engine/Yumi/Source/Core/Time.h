#pragma once

namespace Yumi
{
    class Time : public Singleton<Time>
    {
        YSINGLETON_FRIEND(Time)
    public:
        void CalculateTimeStep();

        float MaxDeltaTime = 1.f / 15.f;
        float FixedDeltaTime = 0.0166f;
        uint32_t TargetFrameRate = 60;
        float  DeltaTime() { return static_cast<float>(s_DeltaTime); }
        float  ApplicationTime() { return static_cast<float>(s_ApplicationTime); }
        uint32_t FrameRate() { return (uint32_t) ((double) s_ApplicationFrames / s_ApplicationTime); }
        uint32_t ApplicationFrames() { return s_ApplicationFrames; }
        uint32_t FixedUpdateCalls() { return s_FixedUpdateCalls; }

    private:
        Time();
        ~Time();

        double s_DeltaTime = 0;
        double s_ApplicationTime = 0;
        uint32_t s_ApplicationFrames = 0;
        uint32_t s_FixedUpdateCalls = 0;
        double s_FixedUpdateTimer = 0;
        double s_LastTime = 0;
    };
}