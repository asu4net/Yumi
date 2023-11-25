#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class AnimationSystem : public System
    {
    public:
        AnimationSystem(const SharedPtr<Scene>& scene);

        int GetExecutionOrder() const { return SystemExecutionOrder::AnimationSystemIndex; };
        void OnStart() override;
        void OnUpdate() override;
        void OnFinish() override;

    private:
        void OnAnimationComponentAdded(entt::registry&, const entt::entity entity);
    };
}