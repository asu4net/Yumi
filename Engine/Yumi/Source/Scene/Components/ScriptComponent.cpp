#include "ScriptComponent.h"

namespace Yumi
{
    void ScriptStatics::Detach(Actor& actor)
    {
        ScriptComponent& scriptComponent = actor.Get<ScriptComponent>();
        YCHECK(scriptComponent.ScriptInstance, "There is no script attached!");

        if (ShouldCallRuntimeMethods(actor))
            scriptComponent.ScriptInstance->Finish();

        scriptComponent.ScriptInstance->Destroy();
        scriptComponent.ScriptInstance.reset();
    }
}