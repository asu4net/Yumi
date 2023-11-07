#pragma once
#include "Rendering/Actor.h"

namespace Yumi
{
    class Scene;

    class System
    {
    public:
        System(const SharedPtr<Scene>& scene);

        Scene& GetScene() const;
        entt::registry& GetRegistry() const;

        Actor GetActorFromEntity(entt::entity entity);
        
        virtual int GetExecutionOrder() const { return INT_MAX; }

        virtual void OnCreate();
        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnFixedUpdate();
        virtual void OnFinish();
        virtual void OnDestroy();

    private:
        SharedPtr<Scene> m_Scene;
    };
}