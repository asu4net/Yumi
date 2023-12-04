#pragma once
#include "System.h"
#include "SystemExecutionOrder.h"

namespace Yumi
{
    struct ScriptComponent;

    class ScriptSystem : public System
    {
    public:
        static void UpdateScriptInstance(ScriptComponent& scriptComponent);
        
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