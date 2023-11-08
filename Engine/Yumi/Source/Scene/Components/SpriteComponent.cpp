#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"

namespace Yumi
{

    void SpriteStatics::UpdateTransformMatrix(Actor& actor)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        const Matrix4 actorTransformMatrix = actor.Transform.GetMatrix();
        if (sprite.TransformMatrix == actorTransformMatrix)
            return;

        sprite.TransformMatrix = actorTransformMatrix;
        UpdateVertexPositions(actor);
    }

    void SpriteStatics::UpdateVertexPositions(Actor& actor)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        
        const Array<Vector3, 4>& localVertexPositions = sprite.SpriteSource.IsValid() ?
            sprite.SpriteSource->GetVertexPositions() : Graphics::GetDefaultSpriteVertexPositions();

        for (uint32_t i = 0; i < 4; i++)
        {
            sprite.VertexPositions[i] = sprite.TransformMatrix * Vector4(localVertexPositions[i], 1.);
            sprite.VertexPositions[i].x *= sprite.Size.x;
            sprite.VertexPositions[i].y *= sprite.Size.y;
        }
    }

    void SpriteStatics::UpdateVertexUVs(Actor& actor)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.VertexUVs = sprite.SpriteSource.IsValid() ? 
            sprite.SpriteSource->GetVertexUVs() : Graphics::GetDefaultSpriteUVs();

        for (Vector2& vertexUV : sprite.VertexUVs)
        {
            vertexUV.x *= sprite.UVScale.x;
            vertexUV.y *= sprite.UVScale.y;
        }

        Graphics::FlipVertexUVs(sprite.FlipMode, sprite.VertexUVs);
    }

    void SpriteStatics::SetTintColor(Actor& actor, const Color& color)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        
        sprite.TintColor = color;
        for (Color& vertexColor : sprite.VertexColors)
            vertexColor = color;
    }

    void SpriteStatics::SetFlip(Actor& actor, Flip flip)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.FlipMode = flip;
        Graphics::FlipVertexUVs(flip, sprite.VertexUVs);
    }

    void SpriteStatics::SetSize(Actor& actor, const Vector2& size)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.Size = size;
        UpdateVertexPositions(actor);
    }

    void SpriteStatics::SetUVScale(Actor& actor, const Vector2& uvScale)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.UVScale = uvScale;
        UpdateVertexUVs(actor);
    }

    void SpriteStatics::SetSpriteSource(Actor& actor, const AssetLink<Sprite>& spriteSource)
    {
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.SpriteSource = spriteSource;

        UpdateVertexPositions(actor);
        UpdateVertexUVs(actor);
    }
}