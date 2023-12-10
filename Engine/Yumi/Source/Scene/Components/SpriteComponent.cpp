#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"
#include "Core\Engine.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(SpriteComponent);

    SpriteComponent::SpriteComponent(const String& spriteAssetName, SpriteSource source)
        : SpriteAssetRef(GetAssetManager().GetAssetByName(spriteAssetName))
        , Source(source)
    {
    }
}

RTTR_REGISTRATION
{
    using namespace Yumi;
    
    rttr::registration::class_<SpriteComponent>("SpriteComponent")
        .constructor<>()(rttr::policy::ctor::as_object)
        .property("IsVisible", &SpriteComponent::IsVisible)
        .property("OrderInLayer", &SpriteComponent::OrderInLayer)
        .property("SpriteAssetRef", &SpriteComponent::SpriteAssetRef)
        .property("Source", &SpriteComponent::Source)
        .property("SubSpriteName", &SpriteComponent::SubSpriteName)
        .property("Size", &SpriteComponent::Size)
        .property("TintColor", &SpriteComponent::TintColor)
        .property("FlipMode", &SpriteComponent::FlipMode)
        .property("UVScale", &SpriteComponent::UVScale);

    ComponentReflection::RegisterComponentType<SpriteComponent>();
}