#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class CameraSystem : public System
    {
    public:
        CameraSystem(const SharedPtr<Scene>& scene);
        
        Actor GetMainCameraActor() const { return m_MainCameraActor; }
        Actor GetEditorCameraActor() const { return m_EditorCameraActor; }
        
        int GetExecutionOrder() const override { return SystemExecutionOrder::CameraSystemIndex; }
        void OnUpdate() override;

    private:
        Actor m_MainCameraActor;
        Actor m_EditorCameraActor;
    };
}