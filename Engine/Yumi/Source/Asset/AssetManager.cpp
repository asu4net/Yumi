#include "AssetManager.h"
#include "Rendering\Shader.h"

namespace Yumi
{
    AssetManager::AssetManager(const String& workingDirectory, GraphicsAPI api)
        : m_WorkingDirectory(workingDirectory)
        , m_GraphicsApi(api)
    {
    }

    AssetManager::~AssetManager()
    {

    }
}