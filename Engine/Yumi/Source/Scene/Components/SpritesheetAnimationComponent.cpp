#include "SpriteSheetAnimationComponent.h"
#include "Scene\Actor.h"
#include "Core\Engine.h"
#include "Asset\AssetManager.h"

namespace Yumi
{ 
    SpritesheetAnimation& SpriteSheetAnimationStatics::PushAnimation(Actor& actor, const String& name, float timeBetweenSprites, bool shouldLoop)
    {
        SpritesheetAnimationComponent& animationComponent = actor.Get<SpritesheetAnimationComponent>();
        YCHECK(!animationComponent.Animations.count(name), "Animation name in use!");
        animationComponent.Animations[name] = CreateSharedPtr<SpritesheetAnimation>(name, timeBetweenSprites, shouldLoop);
        SpritesheetAnimation& animation = *animationComponent.Animations[name].get();
        if (animationComponent.Animations.empty())
            animationComponent.CurrentAnimation = animation.Name;
        return animation;
    }

    SpritesheetAnimation& SpriteSheetAnimationStatics::GetAnimation(Actor& actor, const String& name)
    {
        SpritesheetAnimationComponent& animationComponent = actor.Get<SpritesheetAnimationComponent>();
        YCHECK(animationComponent.Animations.count(name), "Invalid animation!");
        SpritesheetAnimation& animation = *animationComponent.Animations[name].get();
        return animation;
    }

    void SpriteSheetAnimationStatics::PopAnimation(Actor& actor, const String& name)
    {
        SpritesheetAnimationComponent& animationComponent = actor.Get<SpritesheetAnimationComponent>();
        YCHECK(animationComponent.Animations.count(name), "Invalid animation!");
        animationComponent.Animations.erase(name);
    }

    void SpriteSheetAnimationStatics::SetCurrentAnimation(Actor& actor, const String& name)
    {
        SpritesheetAnimationComponent& animationComponent = actor.Get<SpritesheetAnimationComponent>();
        YCHECK(animationComponent.Animations.count(name), "Invalid animation!");
        animationComponent.CurrentAnimation = name;
    }

    void SpriteSheetAnimationStatics::PushSpritesheet(SpritesheetAnimation& animation, const String& textureAtlasName, 
        const Vector2& tileSize, DynamicArray<Vector2>& atlasLocations)
    {
        AssetRef atlasTextureRef = GetAssetManager().GetAssetByName(textureAtlasName);
        
        for (const Vector2& location : atlasLocations)
        {
            const String subTextureName = textureAtlasName + std::to_string(location.x) + std::to_string(location.y);
            AssetRef spriteRef = GetAssetManager().GetAssetByName(subTextureName + " [Sprite]");
            
            if (!spriteRef.IsValid())
            {
                AssetRef subTextureRef = GetAssetManager().GetAssetByName(subTextureName);
                if (!subTextureRef.IsValid())
                {
                    GetAssetManager().CreateSubTextureAsset(AssetData{subTextureName}, atlasTextureRef, location, tileSize);
                }
                
                spriteRef = GetAssetManager().CreateSpriteAsset(subTextureName);
            }
            animation.Sprites.push_back(spriteRef);
        }
    }

}