#pragma once
#include "Asset\AssetRef.h"

namespace Yumi
{
    struct AnimationComponent
    {
        AnimationComponent() = default;

        AnimationComponent(const AssetRef& animationRef)
            : CurrentAnimation(animationRef)
        {}

        AssetRef CurrentAnimation;
        bool PlayOnStart = true;
    };
}