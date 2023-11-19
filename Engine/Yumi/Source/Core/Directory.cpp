#include "Directory.h"

namespace Yumi
{
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

    String GetAssetsFolderName()
    {
        static const String s_AssetFolderName = "Assets";
        return s_AssetFolderName;
    }
}