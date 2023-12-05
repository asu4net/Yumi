#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(SpriteComponent);
}

RTTR_REGISTRATION
{
    using namespace Yumi;
    
    rttr::registration::enumeration<Flip>("Flip")
    (
        rttr::value("None", Flip::None),
        rttr::value("X", Flip::X),
        rttr::value("Y", Flip::Y),
        rttr::value("Both", Flip::Both)
    );

    rttr::registration::class_<SpriteComponent>("SpriteComponent")
        .constructor<>()
        .property("IsVisible", &SpriteComponent::IsVisible)
        .property("OrderInLayer", &SpriteComponent::OrderInLayer)
        .property("SpriteAssetRef", &SpriteComponent::SpriteAssetRef)
        .property("Size", &SpriteComponent::Size)
        .property("TintColor", &SpriteComponent::TintColor)
        .property("FlipMode", &SpriteComponent::FlipMode)
        .property("UVScale", &SpriteComponent::UVScale);

    ComponentReflection::RegisterComponentType<SpriteComponent>();
}