#include "Globals.h"
#include "Engine.h"
#include "Time.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"

namespace Yumi
{
    Engine& CreateEngine()
    {
        return Engine::CreateInstance();
    }

    void DestroyEngine()
    {
        Engine::DestroyInstance();
    }

    Engine& GetEngine()
    {
        return Engine::GetInstance();
    }

    Time& GetTime()
    {
        return Time::GetInstance();
    }

    float GetDeltaTime()
    {
        return GetTime().DeltaTime();
    }

    Input& GetInput()
    {
        return Input::GetInstance();
    }

    AssetManager& GetAssetManager()
    {
        return AssetManager::GetInstance();
    }

    String GetWorkingDirectory()
    {
        static String workingDirectory;
        if (workingDirectory.empty())
        {
            char buffer[MAX_PATH];
            GetModuleFileNameA(nullptr, buffer, MAX_PATH);
            const String::size_type pos = String(buffer).find_last_of("\\/");
            workingDirectory = String(buffer).substr(0, pos);
        }
        return workingDirectory;
    }

    Yumi::String GetAssetsFolderName()
    {
        static const String s_AssetFolderName = "Assets";
        return s_AssetFolderName;
    }
}