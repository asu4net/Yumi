#pragma once
#include "Asset\AssetRef.h"

namespace Yumi
{
    struct SpritesheetAnimation
    {
        String Name;
        float TimeBetweenSprites = 0;
        bool ShouldLoop = false;
        DynamicArray<AssetRef> Sprites;
        uint32_t CurrentIndex = 0;

        SpritesheetAnimation(String name, float timeBetweenSprites, bool shouldLoop)
            : Name(name)
            , TimeBetweenSprites(timeBetweenSprites)
            , ShouldLoop(shouldLoop)
        {
        }
    };

    struct SpritesheetAnimationComponent
    {
        Map<String, SharedPtr<SpritesheetAnimation>> Animations;
        String CurrentAnimation;
    };

    class Actor;

    struct SpriteSheetAnimationStatics
    {
        static SpritesheetAnimation& PushAnimation(Actor& actor, const String& name, float timeBetweenSprites = .15f, bool shouldLoop = true);
        static SpritesheetAnimation& GetAnimation(Actor& actor, const String& name);
        static void PopAnimation(Actor& actor, const String& name);
        static void SetCurrentAnimation(Actor& actor, const String& name);
        
        static void PushSpritesheet(SpritesheetAnimation& animation, const String& textureAtlasName, 
            const Vector2& tileSize, DynamicArray<Vector2>& atlasLocations);
    };
}