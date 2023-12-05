#include "AnimationComponent.h"
#include "Scene/Actor.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(AnimationComponent)
}

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<AnimationComponent>("AnimationComponent")
        .constructor<>()
        .property("CurrentAnimation", &AnimationComponent::CurrentAnimation)
        .property("PlayOnStart", &AnimationComponent::PlayOnStart)
        .property("CurrentIndex", &AnimationComponent::CurrentIndex)
        .property("CurrentTime", &AnimationComponent::CurrentTime)
        .property("LoopEnabled", &AnimationComponent::LoopEnabled)
        .property("IsPlaying", &AnimationComponent::IsPlaying);

    ComponentReflection::RegisterComponentType<AnimationComponent>();
}