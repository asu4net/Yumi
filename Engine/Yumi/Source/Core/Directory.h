#pragma once
#include <filesystem>

namespace Yumi
{
    String GetWorkingDirectory();
    String GetAssetsFolderName();
    void GetAssetDirectoryLocalPath(const String& filePath, String& localPath);
}