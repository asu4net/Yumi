#pragma once
#include "Asset\AssetRef.h"

namespace Yumi
{
    struct AnimationComponent
    {
        AssetRef CurrentAnimation;
        bool PlayOnStart = true;
        AssetRef* Target = nullptr; //TODO: Esto en reflexión como que no va a funcionar, mal pensado
        uint32_t CurrentIndex = 0;
        float CurrentTime = 0.f;
        bool LoopEnabled = true;
        bool IsPlaying = false;

        AnimationComponent() = default;

        AnimationComponent(const AssetRef& animationRef, AssetRef* target)
            : CurrentAnimation(animationRef)
            , Target(target)
        {}

        RTTR_ENABLE_NO_VIRTUAL
    };
}