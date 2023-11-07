#include "SpriteSystem.h"
#include "Rendering\Renderer.h"
#include "..\Components\SpriteComponent.h"
#include "..\Components\TransformComponent.h"

namespace Yumi
{
    void SpriteSystem::OnCreate()
    {
        GetRegistry().on_construct<SpriteSystem>().connect<&SpriteSystem::OnSpriteComponentAdded>(this);
        GetRegistry().on_update<SpriteSystem>().connect<&SpriteSystem::OnSpriteComponentUpdated>(this);
        GetRegistry().on_destroy<SpriteSystem>().connect<&SpriteSystem::OnSpriteComponentRemoved>(this);
    }

    void SpriteSystem::OnStart()
    {
    }

    void SpriteSystem::OnUpdate()
    {
        
    }

    void SpriteSystem::OnFixedUpdate()
    {
    }

    void SpriteSystem::OnFinish()
    {
        GetRegistry().on_construct<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentAdded>(this);
        GetRegistry().on_update<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentUpdated>(this);
        GetRegistry().on_destroy<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentRemoved>(this);
    }

    void SpriteSystem::OnSpriteComponentAdded(entt::registry&, const entt::entity entity)
    {
        Renderer& renderer = Renderer::GetInstance();
        Actor spriteActor = GetActorFromEntity(entity);
        SpriteComponent& sprite = spriteActor.Get<SpriteComponent>();
        TransformComponent& transform = spriteActor.Get<TransformComponent>();

        if (sprite.SubTexture.IsValid())
        {
            sprite.Texture = sprite.SubTexture->GetParent();
        }

        Sprite::Configuration cfg;
        cfg.IsVisible = sprite.IsVisible;
        cfg.FlipMode = sprite.FlipMode;
        cfg.Size = sprite.Size;
        cfg.Transform = Matrix4::CreateTransform(transform.Position, transform.Rotation, transform.Scale);
        cfg.UVScale = sprite.UVScale;
        cfg.TintColor = sprite.TintColor;

        Id id = 0;

        if (sprite.SubTexture.IsValid())
        {
            id = renderer.CreateSprite(sprite.SubTexture, cfg);
        }
        else if (sprite.Texture.IsValid())
        {
            id = renderer.CreateSprite(sprite.Texture, cfg);
        }
        else
        {
            id = renderer.CreateSprite(cfg);
        }

        Id* nonConstId = const_cast<Id*>(&sprite.SpriteId);
        *nonConstId = id;
    }

    void SpriteSystem::OnSpriteComponentUpdated(entt::registry&, const entt::entity entity)
    {
        Renderer& renderer = Renderer::GetInstance();
        Actor spriteActor = GetActorFromEntity(entity);
        SpriteComponent& spriteComponent = spriteActor.Get<SpriteComponent>();
        
        Sprite& sprite = renderer.GetSprite(spriteComponent.SpriteId);

        if (sprite.IsVisible() != spriteComponent.IsVisible)
            sprite.SetVisible(spriteComponent.IsVisible);

        if (sprite.GetFlip() != spriteComponent.FlipMode)
            sprite.SetFlip(spriteComponent.FlipMode);

        if (sprite.GetSize() != spriteComponent.Size)
            sprite.SetSize(spriteComponent.Size);

        if (sprite.GetUVScale() != spriteComponent.UVScale)
            sprite.SetUVScale(spriteComponent.UVScale);

        if (sprite.GetTintColor() != spriteComponent.TintColor)
            sprite.SetTintColor(spriteComponent.TintColor);

        if (spriteComponent.SubTexture.IsValid())
            spriteComponent.Texture = spriteComponent.SubTexture->GetParent();

        if (sprite.GetSubTexture() != spriteComponent.SubTexture)
            sprite.SetTexture(spriteComponent.SubTexture);
        else if (sprite.GetTexture() != spriteComponent.Texture)
            sprite.SetTexture(spriteComponent.Texture);
    }

    void SpriteSystem::OnSpriteComponentRemoved(entt::registry&, const entt::entity entity)
    {
        SpriteComponent& sprite = GetActorFromEntity(entity).Get<SpriteComponent>();
        Renderer::GetInstance().DestroySprite(sprite.SpriteId);
    }
}