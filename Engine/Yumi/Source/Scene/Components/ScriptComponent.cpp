#include "ScriptComponent.h"

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::enumeration<ScriptExecutionContext>("ScriptExecutionContext")
    (
        rttr::value("Runtime", ScriptExecutionContext::Runtime),
        rttr::value("OutOfRuntime", ScriptExecutionContext::OutOfRuntime),
        rttr::value("Always", ScriptExecutionContext::Always)
    );
    
    rttr::registration::class_<ScriptComponent>("ScriptComponent")
        .constructor<>()
        .property("ScriptType", &ScriptComponent::ScriptType)
        .property("ExecutionOrder", &ScriptComponent::ExecutionOrder)
        .property("ExecutionContext", &ScriptComponent::ExecutionContext);

    ComponentReflection::RegisterComponentType<ScriptComponent>();
}