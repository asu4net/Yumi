#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    struct TransformComponent;

    class SpriteSystem : public System
    {
    public:
        SpriteSystem(Scene* scene);

        void OnSpriteComponentAdded(entt::registry&, const entt::entity entity);
        int GetExecutionOrder() const { return SystemExecutionOrder::SpriteSystemIndex; };
        
        void OnUpdate() override;
    };
}