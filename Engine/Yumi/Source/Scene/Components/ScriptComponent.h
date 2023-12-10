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

    // INFO: Estos scripts son bastante placeholder
    // TODO: Hacer que los scripts hereden de Asset e integrarlos en ciclo de ejecución de los mismos
    struct ScriptComponent
    {
        String ScriptType;
        uint32_t ExecutionOrder = 0;
        ScriptExecutionContext ExecutionContext = ScriptExecutionContext::Runtime;
        
        String PrevScriptType;
        Actor OwnerActor;
        SharedPtr<Script> ScriptInstance;
        Scene* OwnerScene = nullptr;

        ScriptComponent() = default;
        
        ScriptComponent(const String& scriptType)
            : ScriptType(scriptType)
        {}

        ScriptComponent(Type type)
            : ScriptType(type.get_name().to_string())
        {}
    };

    YFORCE_LINK(ScriptComponent)

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
    };
}