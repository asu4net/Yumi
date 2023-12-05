#include "TransformComponent.h"

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<TransformComponent>("TransformComponent")
        .constructor<>()
        .property("Position", &TransformComponent::Position)
        .property("Rotation", &TransformComponent::Rotation)
        .property("Scale", &TransformComponent::Scale);

    ComponentReflection::RegisterComponentType<TransformComponent>();
}

namespace Yumi
{
    YFORCE_LINK_IMPL(TransformComponent)
}