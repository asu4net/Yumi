#pragma once
#include "Asset/AssetLink.h"
#include "Scene.h"

namespace Yumi
{
    class Scene;

    class World : public Singleton<World>
    {
        YSINGLETON_FRIEND(World)
    public:
        void OpenScene(const String& sceneName);
        const AssetLink<Scene>& GetActiveScene() { return m_ActiveScene; }

        void Start();
        void Update();
        void FixedUpdate();
        void Finish();

    private:
        AssetLink<Scene> m_ActiveScene;
        
        World();
        ~World();
    };
}