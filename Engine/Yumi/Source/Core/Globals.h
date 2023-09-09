#pragma once

namespace Yumi
{
    class Engine& CreateEngine();
    void DestroyEngine();

    Engine& GetEngine();
    class Time& GetTime();
    float GetDeltaTime();
    class Input& GetInput();
    class AssetManager& GetAssetManager();

    String GetWorkingDirectory();
}