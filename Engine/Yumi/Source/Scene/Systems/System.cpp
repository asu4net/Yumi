#include "System.h"
#include "Scene/Scene.h"

namespace Yumi
{
    System::System(Scene* scene)
        : m_Scene(scene)
    {
        YCHECK(m_Scene, "A valid scene is required");
    }
    
    Scene* System::GetScenePtr() const
    {
        YCHECK(m_Scene, "Scene is not valid");
        return m_Scene;
    }

    Scene& System::GetScene() const
    {
        return *m_Scene;
    }

    entt::registry& System::GetRegistry() const
    {
        WeakPtr<entt::registry> registry = m_Scene->GetRegistry();
        YCHECK(!registry.expired(), "Registry is not valid");
        return *registry.lock();
    }

    Actor System::GetActorFromEntity(entt::entity entity)
    {
        return Actor(entity, m_Scene->GetRegistry());
    }

    void System::OnStart()
    {
    }

    void System::OnUpdate()
    {
    }

    void System::OnFixedUpdate()
    {
    }

    void System::OnSubmitGizmos()
    {
    }

    void System::OnFinish()
    {
    }
}