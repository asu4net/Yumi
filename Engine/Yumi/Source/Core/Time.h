#pragma once

namespace Yumi
{
    class Time
    {
    public:
        static void Start();
        static void CalculateTimeStep();

        inline static float MaxDeltaTime = 1.f / 15.f;
        inline static float FixedDeltaTime = 0.0166f;
        inline static uint32_t TargetFrameRate = 60;

        inline static float  DeltaTime() { return static_cast<float>(s_DeltaTime); }
        inline static float  ApplicationTime() { return static_cast<float>(s_ApplicationTime); }
        
        inline static uint32_t FrameRate() { return (uint32_t) ((double) s_ApplicationFrames / s_ApplicationTime); }
        inline static uint32_t ApplicationFrames() { return s_ApplicationFrames; }
        inline static uint32_t FixedUpdateCalls() { return s_FixedUpdateCalls; }

    private:
        inline static double s_DeltaTime = 0;
        inline static double s_ApplicationTime = 0;
        inline static uint32_t s_ApplicationFrames = 0;
        inline static uint32_t s_FixedUpdateCalls = 0;

        inline static double s_FixedUpdateTimer = 0;
        inline static double s_LastTime = 0;
        //inline static LARGE_INTEGER s_LastTime{};
        //inline static LARGE_INTEGER s_Frec{};

        //static LARGE_INTEGER GetTime();
    };
}