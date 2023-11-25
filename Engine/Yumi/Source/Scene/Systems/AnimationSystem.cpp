#include "AnimationSystem.h"
#include "Scene\Components\AnimationComponent.h"
#include "Scene\Components\SpriteComponent.h"
#include "Animation\Animation.h"

namespace Yumi
{
    AnimationSystem::AnimationSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
        GetRegistry().on_construct<AnimationSystem>().connect<&AnimationSystem::OnAnimationComponentAdded>(this);
    }

    void AnimationSystem::OnAnimationComponentAdded(entt::registry&, const entt::entity entity)
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

            Animation& animation = animationComponent.CurrentAnimation.GetAs<Animation>();
            animation.Play();
        });
    }

    void AnimationSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<SpriteComponent, AnimationComponent>();

        view.each([&](entt::entity entity, SpriteComponent& spriteComponent, AnimationComponent& animationComponent) {
            
            if (!animationComponent.CurrentAnimation.IsValid())
            {
                return;
            }

            Animation& animation = animationComponent.CurrentAnimation.GetAs<Animation>();
            animation.SetTarget(&spriteComponent.SpriteAssetRef);
            animation.Update();
        });
    }

    void AnimationSystem::OnFinish()
    {
        GetRegistry().on_construct<AnimationSystem>().disconnect<&AnimationSystem::OnAnimationComponentAdded>(this);
    }
}