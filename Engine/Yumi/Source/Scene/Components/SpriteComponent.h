#pragma once
#include "Asset\AssetRef.h"
#include "Rendering\Sprite.h"

namespace Yumi
{
    struct SpriteComponent
    {
        Matrix4 TransformMatrix;
        bool IsVisible = true;
        AssetRef SpriteAssetRef;
        Color TintColor = Color::White;
        Vector2 Size = Vector2::One;
        Flip FlipMode = Flip::None;
        Vector2 UVScale = Vector2::One;
        int OrderInLayer = 0;

        Array<Vector3, 4> VertexPositions;
        Array<Vector2, 4> VertexUVs;
        Array<Color, 4> VertexColors;

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