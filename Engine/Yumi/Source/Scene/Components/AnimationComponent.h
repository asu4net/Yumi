#pragma once
#include "Asset\AssetRef.h"

namespace Yumi
{
    struct AnimationComponent
    {
        AssetRef CurrentAnimation;
        bool PlayOnStart = true;
        uint32_t CurrentIndex = 0;
        float CurrentTime = 0.f;
        bool LoopEnabled = true;
        bool IsPlaying = false;

        AnimationComponent() = default;

        AnimationComponent(const AssetRef& animationRef)
            : CurrentAnimation(animationRef)
        {}

        AnimationComponent(const String& animationAssetName);

        RTTR_ENABLE_NO_VIRTUAL
    };

    YFORCE_LINK(AnimationComponent)
}