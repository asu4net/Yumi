#include "ScriptComponent.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(ScriptComponent)
}

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
        .constructor<>()(rttr::policy::ctor::as_object)
        .property("ScriptType", &ScriptComponent::ScriptType)
        .property("ExecutionOrder", &ScriptComponent::ExecutionOrder)
        .property("ExecutionContext", &ScriptComponent::ExecutionContext);

    ComponentReflection::RegisterComponentType<ScriptComponent>();
}