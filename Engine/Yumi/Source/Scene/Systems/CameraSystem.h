#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class CameraSystem : public System
    {
    public:
        CameraSystem(Scene* scene);
        
        void SetMainCameraActor(Actor actor);
        Actor GetMainCameraActor() const { return m_MainCameraActor; }
        
        int GetExecutionOrder() const override { return SystemExecutionOrder::CameraSystemIndex; }
        void OnUpdate() override;

    private:
        Actor m_MainCameraActor;
    };
}