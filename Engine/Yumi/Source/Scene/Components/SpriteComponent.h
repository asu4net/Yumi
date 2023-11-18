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

    class Actor;

    struct SpriteStatics
    {
        static void UpdateTransformMatrix(Actor& actor);
        static void UpdateVertexPositions(Actor& actor);
        static void UpdateVertexUVs(Actor& actor);
        static void SetTintColor(Actor& actor, const Color& color);
        static void SetFlip(Actor& actor, Flip flip);
        static void SetSize(Actor& actor, const Vector2& size);
        static void SetUVScale(Actor& actor, const Vector2& uvScale);
        static void SetSpriteAssetRef(Actor& actor, const AssetRef& spriteSourceRef);
    };
}