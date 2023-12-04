#include "InformationComponent.h"
#include "Scene/Actor.h"

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<InformationComponent>("InformationComponent")
        .constructor<>()
        .property("Name", &InformationComponent::Name)
        .property("ID", &InformationComponent::ID)
        .property("IsSerializable", &InformationComponent::IsSerializable);

    ComponentReflection::RegisterComponentType<InformationComponent>();
}