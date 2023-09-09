#pragma once
#include "Asset.h"
#include "AssetLink.h"

namespace Yumi
{
    class AssetManager : public Singleton<AssetManager>
    {
        YSINGLETON_FRIEND(AssetManager)
    private:
        AssetManager(const String& workingDirectory);
        ~AssetManager();

        String m_WorkingDirectory;
        Map<Id, Shared<Asset>> m_IdAssetMap;
        Map<String, Id> m_NameIdMap;
    };
}