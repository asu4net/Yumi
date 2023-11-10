#pragma once
#include "Scene\Actor.h"

namespace Yumi
{
    class Scene;

    class System
    {
    public:
        System(const SharedPtr<Scene>& scene);
        
        const SharedPtr<Scene>& GetScenePtr() const;
        Scene& GetScene() const;
        entt::registry& GetRegistry() const;

        Actor GetActorFromEntity(entt::entity entity);
        
        virtual int GetExecutionOrder() const { return INT_MAX; }

        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnFixedUpdate();
        virtual void OnFinish();

    private:
         SharedPtr<Scene> m_Scene;
    };
}