#include "Actor.h"
#include "Components/TransformComponent.h"
#include "Components/InformationComponent.h"

namespace Yumi
{
    Actor::Actor()
        : Transform(TransformComponent())
        , Information(InformationComponent())
    {
    }
    
    Actor::Actor(const entt::entity entity, const WeakPtr<entt::registry>& registry)
        : m_Entity(entity)
        , m_Registry(registry)
        , Transform(Get<TransformComponent>())
        , Information(Get<InformationComponent>())
    {
    }
}