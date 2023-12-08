#include "ScriptSystem.h"
#include "System.h"
#include "Scene\Scene.h"
#include "Scene\Components\ScriptComponent.h"

namespace Yumi
{
    void ScriptSystem::UpdateScriptInstance(ScriptComponent& scriptComponent)
    {
        YCHECK(scriptComponent.OwnerActor.IsValid(), "Owner actor should be initialized!");
        YCHECK(scriptComponent.OwnerScene, "Owner scene should be initialized!");

        // If the script type has not changed do nothing
        if (scriptComponent.ScriptType == scriptComponent.PrevScriptType)
        {
            return;
        }

        // Otherwise if there was a previous instance dispose it
        if (scriptComponent.ScriptInstance)
        {
            scriptComponent.ScriptInstance->Finish();
            scriptComponent.ScriptInstance->Destroy();
            scriptComponent.ScriptInstance = nullptr;
        }
        
        // Clean the previous script type
        scriptComponent.PrevScriptType = "";

        Type scriptType = Type::get_by_name(scriptComponent.ScriptType);

        // If the new script type is not valid clean and do nothing
        if (!scriptType.is_valid() || !scriptType.is_derived_from(Type::get<Script>()))
        {
            scriptComponent.ScriptType = "";
            return;
        }
        
        // Otherwise create an instance of the new script type
        SharedPtr<Script> scriptInstance = scriptType.create().get_value<SharedPtr<Script>>();
        scriptInstance->m_Scene = scriptComponent.OwnerScene;
        scriptInstance->m_Actor = scriptComponent.OwnerActor;
        scriptInstance->Create();

        scriptComponent.ScriptInstance = scriptInstance;

        // Update the previous script type
        scriptComponent.PrevScriptType = scriptComponent.ScriptType;

        if (ScriptStatics::ShouldCallRuntimeMethods(scriptComponent.OwnerActor) && scriptComponent.OwnerScene->IsStarted())
            scriptInstance->Start();
    }

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

        UpdateScriptInstance(scriptComponent);
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
        view.each([&](entt::entity entity, ScriptComponent& script) {
            UpdateScriptInstance(script);
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

    void ScriptSystem::OnSubmitGizmos()
    {
        auto view = GetRegistry().view<ScriptComponent>();
        view.each([&](entt::entity entity, const ScriptComponent& script) {
            if (!script.ScriptInstance || !ScriptStatics::ShouldCallRuntimeMethods(GetActorFromEntity(entity))) return;
            script.ScriptInstance->SubmitGizmos();
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