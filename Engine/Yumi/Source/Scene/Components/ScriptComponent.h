#pragma once
#include "Scripting\Script.h"
#include "Scene\Actor.h"
#include "Scene\Scene.h"
#include "Scene\World.h"

namespace Yumi
{
    struct ScriptComponent
    {
        UniquePtr<Script> ScriptInstance;
        SharedPtr<Scene> OwnerScene;
        Actor OwnerActor;
        //TODO: script type
    };

    class Actor;

    struct ScriptStatics
    {
        inline static bool ShouldCallRuntimeMethods(const UniquePtr<Script>& script)
        {
            World& world = World::GetInstance();

            const bool isRuntimeEnabled = world.GetActiveScene()->IsRuntimeEnabled();

            switch (script->GetExecutionContext())
            {
            case Script::ExecutionContext::Game:
                if (isRuntimeEnabled)
                    return true;
                return false;
            case Script::ExecutionContext::Editor:
                if (!isRuntimeEnabled)
                    return true;
                return false;
            case Script::ExecutionContext::Both:
                return true;
            default:
                YCHECK(false, "Unhandled case")
                    return false;
            };
        }

        static void Detach(Actor& actor);

        template<typename T>
        inline static void Attach(Actor& actor)
        {
            if (!actor.Has<ScriptComponent>())
                actor.Add<ScriptComponent>();

            ScriptComponent& scriptComponent = actor.Get<ScriptComponent>();
            if (scriptComponent.ScriptInstance)
            {
                scriptComponent.ScriptInstance->Finish();
                scriptComponent.ScriptInstance->Destroy();
            }
            scriptComponent.ScriptInstance = CreateUniquePtr<T>();
            scriptComponent.ScriptInstance->m_Scene = scriptComponent.OwnerScene;
            scriptComponent.ScriptInstance->m_Actor = scriptComponent.OwnerActor;
            scriptComponent.ScriptInstance->Create();

            if (ShouldCallRuntimeMethods(scriptComponent.ScriptInstance))
                scriptComponent.ScriptInstance->Start();
        }
    };
}