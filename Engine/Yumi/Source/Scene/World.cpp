#include "World.h"
#include "Asset\AssetManager.h"
#include "Core\Engine.h"

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
        AssetManager& assetManager = GetAssetManager();
        AssetRef sceneRef = assetManager.GetAssetByName(sceneName);
        YCHECK(sceneRef.IsValid(), "The scene should exist");
        
        if (!m_ActiveScene.expired())
        {
            YLOG_TRACE("Scene closed! %s\n", m_ActiveScene.lock()->GetAssetData().Name.c_str());
            m_ActiveScene.lock()->Finish();
        }

        m_ActiveScene = sceneRef.GetPtrAs<Scene>();
        m_ActiveScene.lock()->Prepare();
        YLOG_TRACE("Scene opened! %s\n", m_ActiveScene.lock()->GetAssetData().Name.c_str());
    }

    void World::Prepare()
    {
        AssetManager& assetManager = GetAssetManager();
        DynamicArray<AssetRef> allScenes;
        assetManager.GetAssetsOfType<Scene>(allScenes);
        
        if (!allScenes.empty())
        {
            for (AssetRef& sceneRef : allScenes)
            {
                SharedPtr<Scene> scene = sceneRef.GetPtrAs<Scene>().lock();
                if (!scene->IsStartScene())
                    continue;
                m_ActiveScene = scene;
            }
            if (m_ActiveScene.expired())
                m_ActiveScene = allScenes[0].GetPtrAs<Scene>();
        }
        else
        {
            AssetRef emptySceneRef = assetManager.CreateSceneAsset({"EmptyScene"});
            m_ActiveScene = emptySceneRef.GetPtrAs<Scene>();
            m_ActiveScene.lock()->SetScenePtr(m_ActiveScene.lock());
        }

        YLOG_TRACE("Scene opened! %s\n", m_ActiveScene.lock()->GetAssetData().Name.c_str());
        m_ActiveScene.lock()->Prepare();
    }

    void World::Start()
    {
        m_ActiveScene.lock()->Start();
    }

    void World::Update()
    {
        m_ActiveScene.lock()->Update();
    }

    void World::FixedUpdate()
    {
        m_ActiveScene.lock()->FixedUpdate();
    }

    void World::Finish()
    {
        m_ActiveScene.lock()->Finish();
    }
}