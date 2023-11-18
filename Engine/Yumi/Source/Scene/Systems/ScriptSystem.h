#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    class ScriptSystem : public System
    {
    public:
        ScriptSystem(const SharedPtr<Scene>& scene);
        ~ScriptSystem();

        int GetExecutionOrder() const override { return SystemExecutionOrder::CameraSystemIndex; }
        
        void OnStart() override;
        void OnUpdate() override;
        void OnFixedUpdate() override;
        void OnFinish() override;
    
    private:
        void OnScriptComponentAdded(entt::registry&, const entt::entity entity);
        void OnScriptComponentDestroyed(entt::registry&, const entt::entity entity);
    };
}