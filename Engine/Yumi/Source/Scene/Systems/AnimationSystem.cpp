#include "AnimationSystem.h"
#include "Scene\Components\AnimationComponent.h"
#include "Scene\Components\SpriteComponent.h"
#include "Animation\Animation.h"
#include "Core\Engine.h"

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

            animationComponent.IsPlaying = true;
        });
    }

    void AnimationSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<AnimationComponent>();
        view.each([&](entt::entity entity, AnimationComponent& animationComponent) { UpdateAnimation(animationComponent); });
    }

    void AnimationSystem::UpdateAnimation(AnimationComponent& animationComponent)
    {
        if (!animationComponent.IsPlaying || !animationComponent.CurrentAnimation.IsValid() || !animationComponent.Target)
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
            *animationComponent.Target = currentKey.KeyAssetRef;
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

    void AnimationSystem::OnFinish()
    {
        GetRegistry().on_construct<AnimationSystem>().disconnect<&AnimationSystem::OnAnimationComponentAdded>(this);
    }
}