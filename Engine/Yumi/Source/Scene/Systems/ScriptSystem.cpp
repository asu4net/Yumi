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

    void ScriptSystem::OnScriptComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor scriptActor = GetActorFromEntity(entity);
        ScriptComponent& scriptComponent = scriptActor.Get<ScriptComponent>();
        scriptComponent.OwnerActor = scriptActor;
        scriptComponent.OwnerScene = GetScenePtr();

        GetRegistry().sort<ScriptComponent>([](const ScriptComponent& a, const ScriptComponent& b)
        {
            return a.ExecutionOrder < b.ExecutionOrder;
        });
    }
    
    void ScriptSystem::OnScriptComponentDestroyed(entt::registry&, const entt::entity entity)
    {
        Actor scriptActor = GetActorFromEntity(entity);
        ScriptComponent& scriptComponent = scriptActor.Get<ScriptComponent>();
        if (!scriptComponent.ScriptInstance) return;

        if (ScriptStatics::ShouldCallRuntimeMethods(scriptActor))
            scriptComponent.ScriptInstance->Finish();

        scriptComponent.ScriptInstance->Destroy();
    }

    void ScriptSystem::OnStart()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(GetActorFromEntity(entity))) return;
            script.ScriptInstance->Start();
        });
    }

    void ScriptSystem::OnUpdate()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(GetActorFromEntity(entity))) return;
            script.ScriptInstance->Update();
        });
    }

    void ScriptSystem::OnFixedUpdate()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(GetActorFromEntity(entity))) return;
            script.ScriptInstance->FixedUpdate();
        });
    }

    void ScriptSystem::OnFinish()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(GetActorFromEntity(entity))) return;
            script.ScriptInstance->Finish();
        });
    }

    ScriptSystem::~ScriptSystem()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance) return;
            script.ScriptInstance->Destroy();
        });
    }
}