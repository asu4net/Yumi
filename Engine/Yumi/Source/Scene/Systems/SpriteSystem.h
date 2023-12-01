#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    struct TransformComponent;

    class SpriteSystem : public System
    {
    public:
        SpriteSystem(const SharedPtr<Scene>& scene);

        int GetExecutionOrder() const { return SystemExecutionOrder::SpriteSystemIndex; };
        void OnUpdate() override;
    };
}