#include "AnimationSystem.h"
#include "Scene\Components\AnimationComponent.h"
#include "Scene\Components\SpriteComponent.h"
#include "Animation\Animation.h"
#include "Core\Engine.h"
#include "..\Scene.h"

namespace Yumi
{
    AnimationSystem::AnimationSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
    }

    void AnimationSystem::OnStart()
    {
        const auto view = GetRegistry().view<AnimationComponent>();

        view.each([&](entt::entity entity, AnimationComponent& animationComponent) {

            if (!animationComponent.PlayOnStart || !animationComponent.CurrentAnimation.IsValid())
            {
                return;
            }

            animationComponent.IsPlaying = true;
        });
    }

    void AnimationSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<AnimationComponent>();
        view.each([&](entt::entity entity, AnimationComponent& animationComponent) { UpdateAnimation(entity, animationComponent); });
    }

    void AnimationSystem::UpdateAnimation(entt::entity entity, AnimationComponent& animationComponent)
    {
        if (!GetScene().IsRuntimeEnabled() || !animationComponent.IsPlaying || !animationComponent.CurrentAnimation.IsValid())
        {
            return;
        }

        Animation& animation = animationComponent.CurrentAnimation.GetAs<Animation>();

        if (!animation.GetSize())
        {
            return;
        }

        animationComponent.CurrentTime += GetDeltaTime();

        const Animation::Key& currentKey = animation.GetKey(animationComponent.CurrentIndex);
        
        if (animationComponent.CurrentTime >= currentKey.KeyTime)
        {
            Actor actor = GetActorFromEntity(entity);

            if (actor.Has<SpriteComponent>())
            {
                auto& spriteComponent = actor.Get<SpriteComponent>();
                spriteComponent.SubSpriteName = currentKey.KeyRef;
            }
            animationComponent.CurrentIndex++;
        }

        if (animationComponent.CurrentIndex == animation.GetSize())
        {
            animationComponent.CurrentTime = 0;
            animationComponent.CurrentIndex = 0;

            if (!animationComponent.LoopEnabled)
            {
                animationComponent.IsPlaying = false;
            }
        }
    }
}