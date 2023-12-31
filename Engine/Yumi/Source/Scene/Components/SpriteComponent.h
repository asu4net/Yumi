#pragma once
#include "Asset\AssetRef.h"
#include "Rendering\Sprite.h"

namespace Yumi
{
    struct SpriteComponent
    {
        bool IsVisible = true;
        int OrderInLayer = 0;

        AssetRef SpriteAssetRef;
        Vector2 Size = Vector2::One;
        Color TintColor = Color::White;
        Flip FlipMode = Flip::None;
        Vector2 UVScale = Vector2::One;

        SpriteComponent() = default;

        SpriteComponent(const AssetRef& spriteAssetRef)
            : SpriteAssetRef(spriteAssetRef)
        {
        }

        SpriteComponent(const Color tintColor)
            : TintColor(tintColor)
        {
        }
    };
}