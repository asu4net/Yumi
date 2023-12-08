#pragma once
#include "Asset/AssetRef.h"
#include "Scene.h"

namespace Yumi
{
    class Scene;

    class World
    {
    public:
        World();
        ~World();

        void OpenScene(const String& sceneName);
        Scene& GetActiveScene() { return *m_ActiveScene.lock().get(); }
        
        void Prepare();
        void Start();
        void Update();
        void FixedUpdate();
        void SubmitGizmos();
        void Finish();

    private:
        WeakPtr<Scene> m_ActiveScene;
    };
}