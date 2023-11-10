#include "Actor.h"
#include "Components/TransformComponent.h"
#include "Components/InformationComponent.h"

namespace Yumi
{    
    Actor::Actor(const entt::entity entity, const WeakPtr<entt::registry>& registry)
        : m_Entity(entity)
        , m_Registry(registry)
    {
    }

    TransformComponent& Actor::GetTransform() const
    {
        return Get<TransformComponent>();
    }

    InformationComponent& Actor::GetInformation() const
    {
        return Get<InformationComponent>();
    }
}