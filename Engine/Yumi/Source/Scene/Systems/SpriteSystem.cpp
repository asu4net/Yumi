#include "SpriteSystem.h"
#include "Rendering\Renderer.h"
#include "..\Components\SpriteComponent.h"
#include "..\Components\TransformComponent.h"

namespace Yumi
{

    SpriteSystem::SpriteSystem(Scene* scene)
        : System(scene)
    {
    }

    void SpriteSystem::OnCreate()
    {
        GetRegistry().on_construct<SpriteComponent>().connect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }

    void SpriteSystem::OnSpriteComponentAdded(entt::registry&, const entt::entity entity)
    {
        Actor actor = GetActorFromEntity(entity);
        SpriteComponent& sprite = actor.Get<SpriteComponent>();
        sprite.TransformMatrix = actor.Transform.GetMatrix();
        SpriteStatics::UpdateVertexPositions(actor);
        SpriteStatics::UpdateVertexUVs(actor);
        SpriteStatics::SetTintColor(actor, sprite.TintColor);
    }

    void SpriteSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<TransformComponent, SpriteComponent>();

        GetRegistry().sort<SpriteComponent>([](const SpriteComponent& a, const SpriteComponent& b)
        {
            return a.OrderInLayer < b.OrderInLayer;
        });

        Renderer& renderer = Renderer::GetInstance();
        
        renderer.Clear();

        view.each([&](entt::entity entity, const TransformComponent&, const SpriteComponent& sprite) {
            
            Actor spriteActor = GetActorFromEntity(entity);
            SpriteComponent& spriteComponent = spriteActor.Get<SpriteComponent>();
            
            if (!spriteComponent.IsVisible)
                return;

            SpriteStatics::UpdateTransformMatrix(spriteActor);

            // Draw
            renderer.Begin();

            renderer.SubmitSpriteData(
                sprite.VertexPositions, 
                sprite.VertexColors, 
                sprite.SpriteSource->GetTexture().Get(), 
                sprite.VertexUVs
            );
            renderer.End();
        });
    }

    void SpriteSystem::OnFinish()
    {
        GetRegistry().on_construct<SpriteSystem>().disconnect<&SpriteSystem::OnSpriteComponentAdded>(this);
    }
}