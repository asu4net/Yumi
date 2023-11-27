#pragma once

namespace Yumi
{
    struct SpritePrimitive
    {
        static SpritePrimitive CreateLine(const Vector2& start, const Vector2& end, const Vector2& normal,
            const Color& color = Color::White, float thickness = .05f);

        static SpritePrimitive CreateRect(const Vector3& position = Vector3::Zero, const Vector3& rotation = Vector3::Zero, const Color& color = Color::White,
            const Vector2& size = Vector2::One, float thickness = .05f);

        static SpritePrimitive CreateCircle(const Vector3& position = Vector3::Zero, const Vector3& rotation = Vector3::Zero, const Color& color = Color::White,
            float radius = 1.f, float thickness = .05f, float fade = .01f);

        Array<Vector3, 4> VertexPositions;
        Array<Color, 4> VertexColors;
        Array<Vector2, 4> VertexUV = Math::GetDefaultSpriteUVs();
        SharedPtr<class RendererTexture2D> Texture = nullptr;

        // Circle stuff
        bool IsCircle = false;
        Array<Vector3, 4> LocalVertexPositions;
        float Thickness = .05f;
        float Fade = .01f;

    };
}