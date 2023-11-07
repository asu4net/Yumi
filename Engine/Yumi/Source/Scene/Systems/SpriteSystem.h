#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class SpriteSystem : public System
    {
    public:
        int GetExecutionOrder() const { return SystemExecutionOrder::SpriteSystemIndex; };
        void OnCreate() override;
        void OnStart() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnFinish() override;

    private:
        void OnSpriteComponentAdded(entt::registry&, const entt::entity entity);
        void OnSpriteComponentUpdated(entt::registry&, const entt::entity entity);
        void OnSpriteComponentRemoved(entt::registry&, const entt::entity entity);
    };
}