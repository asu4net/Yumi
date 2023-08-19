#include "Time.h"

//TODO: Implement target frame rate

namespace Yumi
{
    void Time::Start()
    {
        s_LastTime = GetTime();

        LARGE_INTEGER frec;
        QueryPerformanceFrequency(&frec);
        s_Frec = frec;
    }

    void Time::CalculateTimeStep()
    {
        s_FixedUpdateCalls = 0;
        s_ApplicationFrames++;

        const LARGE_INTEGER time = GetTime();
        const double timeBetweenFrames = static_cast<double>(time.QuadPart - s_LastTime.QuadPart) /
            static_cast<double>(s_Frec.QuadPart);
        s_LastTime = time;

        s_ApplicationTime += timeBetweenFrames;
        s_DeltaTime = std::clamp(timeBetweenFrames, 0., static_cast<double>(MaxDeltaTime));
        s_FixedUpdateTimer += s_DeltaTime;

        while (s_FixedUpdateTimer >= FixedDeltaTime)
        {
            s_FixedUpdateCalls++;
            s_FixedUpdateTimer -= FixedDeltaTime;
        }
    }

    LARGE_INTEGER Time::GetTime()
    {
        LARGE_INTEGER ticks;
        QueryPerformanceCounter(&ticks);
        return ticks;
    }
}