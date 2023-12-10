#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class AnimationSystem : public System
    {
    public:
        AnimationSystem(Scene* scene);

        int GetExecutionOrder() const { return SystemExecutionOrder::AnimationSystemIndex; };
        void OnAnimationComponentAdded(entt::registry&, const entt::entity entity);
        void OnStart() override;
        void OnUpdate() override;
        
    private:
        void UpdateAnimation(entt::entity entity, struct AnimationComponent& animationComponent);
    };
}