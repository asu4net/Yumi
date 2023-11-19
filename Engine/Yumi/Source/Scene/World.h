#pragma once
#include "Asset/AssetRef.h"
#include "Scene.h"

namespace Yumi
{
    class Scene;

    class World : public Singleton<World>
    {
        YSINGLETON_FRIEND(World)
    public:
        void OpenScene(const String& sceneName);
        Scene& GetActiveScene() { return *m_ActiveScene.lock().get(); }
        
        void Prepare();
        void Start();
        void Update();
        void FixedUpdate();
        void Finish();

    private:
        WeakPtr<Scene> m_ActiveScene;
        
        World();
        ~World();
    };

    World& GetWorld();
}