#include "World.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
    World::World() 
    {
        YLOG_TRACE("World created!\n");
    }

    World::~World() 
    {
        YLOG_TRACE("World destroyed!\n");
    }

    void World::OpenScene(const String& sceneName)
    {
        AssetManager& assetManager = AssetManager::GetInstance();
        AssetLink<Scene> m_Scene = assetManager.GetAssetByName<Scene>(sceneName);
        YCHECK(m_Scene.IsValid(), "The scene should exist");
        
        if (m_ActiveScene.IsValid())
        {
            YLOG_TRACE("Scene closed! %s\n", m_ActiveScene->GetAssetData().Name.c_str());
            m_ActiveScene->Finish();
        }

        m_ActiveScene = m_Scene;
        m_ActiveScene->Start();
        YLOG_TRACE("Scene opened! %s\n", m_ActiveScene->GetAssetData().Name.c_str());
    }

    void World::Start()
    {
        AssetManager& assetManager = AssetManager::GetInstance();
        DynamicArray<AssetLink<Scene>> allScenes;
        assetManager.GetAssetsOfType<Scene>(allScenes);
        
        if (!allScenes.empty())
        {
            for (AssetLink<Scene>& scene : allScenes)
            {
                if (!scene->IsStartScene())
                    continue;
                m_ActiveScene = scene;
            }
            if (!m_ActiveScene.IsValid())
                m_ActiveScene = allScenes[0];
        }
        else
        {
            AssetLink<Scene> emptyScene = assetManager.CreateSceneAsset(AssetData{ "EmptyScene" });
            m_ActiveScene = emptyScene;
        }

        YLOG_TRACE("Scene opened! %s\n", m_ActiveScene->GetAssetData().Name.c_str());
        m_ActiveScene->Start();
    }

    void World::Update()
    {
        m_ActiveScene->Update();
    }

    void World::FixedUpdate()
    {
        m_ActiveScene->FixedUpdate();
    }

    void World::Finish()
    {
        m_ActiveScene->Finish();
    }
}