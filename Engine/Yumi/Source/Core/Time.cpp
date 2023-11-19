#include "Time.h"
#include "GLFW/glfw3.h"

//TODO: Implement target frame rate

namespace Yumi
{
    Time::Time()
        : s_LastTime(glfwGetTime())
    {
        YLOG_TRACE("Time created!\n");
    }

    Time::~Time()
    {
        YLOG_TRACE("Time destroyed!\n");
    }

    void Time::CalculateTimeStep()
    {
        s_FixedUpdateCalls = 0;
        s_ApplicationFrames++;

        double time = glfwGetTime();
        /*const LARGE_INTEGER time = GetTime();*/
        /*const double timeBetweenFrames = static_cast<double>(time.QuadPart - s_LastTime.QuadPart) /
            static_cast<double>(s_Frec.QuadPart);*/
        const double timeBetweenFrames = time - s_LastTime;
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

    /*LARGE_INTEGER Time::GetTime()
    {
        LARGE_INTEGER ticks;
        QueryPerformanceCounter(&ticks);
        return ticks;
    }*/

    Time& GetTime()
    {
        return Time::GetInstance();
    }

    float GetDeltaTime()
    {
        return GetTime().DeltaTime();
    }
}