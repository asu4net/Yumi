#include "ScriptSystem.h"
#include "System.h"
#include "Scene\Scene.h"
#include "Scene\Components\ScriptComponent.h"

namespace Yumi
{
    ScriptSystem::ScriptSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
        GetRegistry().on_construct<ScriptComponent>().connect<&ScriptSystem::OnScriptComponentAdded>(this);
        GetRegistry().on_destroy<ScriptComponent>().connect<&ScriptSystem::OnScriptComponentAdded>(this);
    }

    void ScriptSystem::SortScriptsByExecutionOrder()
    {
        GetRegistry().sort<ScriptComponent>([](const ScriptComponent& a, const ScriptComponent& b)
        {
            const int aExecutionOrder = a.ScriptInstance ? INT_MAX : a.ScriptInstance->GetExecutionOrder();
            const int bExecutionOrder = b.ScriptInstance ? INT_MAX : b.ScriptInstance->GetExecutionOrder();
            return aExecutionOrder < bExecutionOrder;
        });
    }

    void ScriptSystem::OnScriptComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor scriptActor = GetActorFromEntity(entity);
        ScriptComponent& scriptComponent = scriptActor.Get<ScriptComponent>();
        scriptComponent.OwnerActor = scriptActor;
        scriptComponent.OwnerScene = GetScenePtr();
    }
    
    void ScriptSystem::OnScriptComponentDestroyed(entt::registry&, const entt::entity entity)
    {
        Actor scriptActor = GetActorFromEntity(entity);
        ScriptComponent& scriptComponent = scriptActor.Get<ScriptComponent>();
        if (!scriptComponent.ScriptInstance) return;

        if (ScriptStatics::ShouldCallRuntimeMethods(scriptComponent.ScriptInstance))
            scriptComponent.ScriptInstance->Finish();

        scriptComponent.ScriptInstance->Destroy();
    }

    void ScriptSystem::OnStart()
    {
        SortScriptsByExecutionOrder();

        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(script.ScriptInstance)) return;
            script.ScriptInstance->Start();
        });
    }

    void ScriptSystem::OnUpdate()
    {
        SortScriptsByExecutionOrder();

        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(script.ScriptInstance)) return;
            script.ScriptInstance->Update();
        });
    }

    void ScriptSystem::OnFixedUpdate()
    {
        SortScriptsByExecutionOrder();

        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(script.ScriptInstance)) return;
            script.ScriptInstance->FixedUpdate();
        });
    }

    void ScriptSystem::OnFinish()
    {
        SortScriptsByExecutionOrder();

        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(script.ScriptInstance)) return;
            script.ScriptInstance->Finish();
        });
    }

    ScriptSystem::~ScriptSystem()
    {
        SortScriptsByExecutionOrder();

        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance) return;
            script.ScriptInstance->Destroy();
        });
    }
}