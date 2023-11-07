#pragma once
#include "Asset\AssetLink.h"
#include "Rendering\Texture2D.h"
#include "Rendering\SubTexture2D.h"

namespace Yumi
{
    struct SpriteComponent
    {
        bool IsVisible = true;
        AssetLink<Texture2D> Texture;
        AssetLink<SubTexture2D> SubTexture;
        Color TintColor = Color::White;
        Vector2 Size = Vector2::One;
        Flip FlipMode = Flip::None;
        Vector2 UVScale = Vector2::One;
        const Id SpriteId = 0;


        SpriteComponent() = default;

        SpriteComponent(const AssetLink<Texture2D>& texture)
            : Texture(texture)
        {
        }

        SpriteComponent(const AssetLink<SubTexture2D>& subTexture)
            : SubTexture(subTexture)
        {
        }

        SpriteComponent(const Color tintColor)
            : TintColor(tintColor)
        {
        }
    };
}