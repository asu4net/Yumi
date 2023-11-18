#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"

namespace Yumi
{

    void SpriteStatics::UpdateTransformMatrix(Actor& actor)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        const Matrix4 actorTransformMatrix = actor.GetTransform().GetMatrix();
        if (spriteComponent.TransformMatrix == actorTransformMatrix)
            return;

        spriteComponent.TransformMatrix = actorTransformMatrix;
        UpdateVertexPositions(actor);
    }

    void SpriteStatics::UpdateVertexPositions(Actor& actor)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        Sprite& sprite = spriteComponent.SpriteAssetRef.GetAs<Sprite>();

        const Array<Vector3, 4>& localVertexPositions = spriteComponent.SpriteAssetRef.IsValid() ?
            sprite.GetVertexPositions() : Graphics::GetDefaultSpriteVertexPositions();

        for (uint32_t i = 0; i < 4; i++)
        {
            spriteComponent.VertexPositions[i] = Vector4(localVertexPositions[i], 1.f) * spriteComponent.TransformMatrix;
            spriteComponent.VertexPositions[i].x *= spriteComponent.Size.x;
            spriteComponent.VertexPositions[i].y *= spriteComponent.Size.y;
        }
    }

    void SpriteStatics::UpdateVertexUVs(Actor& actor)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        Sprite& sprite = spriteComponent.SpriteAssetRef.GetAs<Sprite>();
        spriteComponent.VertexUVs = spriteComponent.SpriteAssetRef.IsValid() ?
            sprite.GetVertexUVs() : Graphics::GetDefaultSpriteUVs();

        for (Vector2& vertexUV : spriteComponent.VertexUVs)
        {
            vertexUV.x *= spriteComponent.UVScale.x;
            vertexUV.y *= spriteComponent.UVScale.y;
        }

        Graphics::FlipVertexUVs(spriteComponent.FlipMode, spriteComponent.VertexUVs);
    }

    void SpriteStatics::SetTintColor(Actor& actor, const Color& color)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        
        spriteComponent.TintColor = color;
        for (Color& vertexColor : spriteComponent.VertexColors)
            vertexColor = color;
    }

    void SpriteStatics::SetFlip(Actor& actor, Flip flip)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        spriteComponent.FlipMode = flip;
        Graphics::FlipVertexUVs(flip, spriteComponent.VertexUVs);
    }

    void SpriteStatics::SetSize(Actor& actor, const Vector2& size)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        spriteComponent.Size = size;
        UpdateVertexPositions(actor);
    }

    void SpriteStatics::SetUVScale(Actor& actor, const Vector2& uvScale)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        spriteComponent.UVScale = uvScale;
        UpdateVertexUVs(actor);
    }

    void SpriteStatics::SetSpriteAssetRef(Actor& actor, const AssetRef& spriteAssetRef)
    {
        SpriteComponent& spriteComponent = actor.Get<SpriteComponent>();
        spriteComponent.SpriteAssetRef = spriteAssetRef;

        UpdateVertexPositions(actor);
        UpdateVertexUVs(actor);
    }
}