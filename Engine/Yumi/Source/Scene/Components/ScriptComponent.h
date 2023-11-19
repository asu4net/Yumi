#pragma once
#include "Scripting\Script.h"
#include "Scene\Actor.h"
#include "Scene\Scene.h"
#include "Scene\World.h"
#include "Core\Engine.h"

namespace Yumi
{
    enum class ScriptExecutionContext
    {
        Runtime,
        OutOfRuntime,
        Always
    };

    struct ScriptComponent
    {
        UniquePtr<Script> ScriptInstance;
        SharedPtr<Scene> OwnerScene;
        Actor OwnerActor;
        int ExecutionOrder = 0;
        ScriptExecutionContext ExecutionContext = ScriptExecutionContext::Runtime;
        //TODO: script type
    };

    class Actor;

    struct ScriptStatics
    {
        inline static bool ShouldCallRuntimeMethods(Actor& actor)
        {
            const ScriptComponent& scriptComponent = actor.Get<ScriptComponent>();
            const bool isRuntimeEnabled = GetWorld().GetActiveScene().IsRuntimeEnabled();

            switch (scriptComponent.ExecutionContext)
            {
            case ScriptExecutionContext::Runtime:
                if (isRuntimeEnabled)
                    return true;
                return false;
            case ScriptExecutionContext::OutOfRuntime:
                if (!isRuntimeEnabled)
                    return true;
                return false;
            case ScriptExecutionContext::Always:
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

            if (ShouldCallRuntimeMethods(actor))
                scriptComponent.ScriptInstance->Start();
        }
    };
}