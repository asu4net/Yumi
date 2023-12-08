#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"
#include "Core\Engine.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(SpriteComponent);

    SpriteComponent::SpriteComponent(const String& spriteAssetName)
        : SpriteAssetRef(GetAssetManager().GetAssetByName(spriteAssetName))
    {
    }
}

RTTR_REGISTRATION
{
    using namespace Yumi;
    
    rttr::registration::class_<SpriteComponent>("SpriteComponent")
        .constructor<>()
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