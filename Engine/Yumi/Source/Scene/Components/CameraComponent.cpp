#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"
#include "Window\Window.h"
#include "Core\Engine.h"

namespace Yumi
{
    YFORCE_LINK_IMPL(CameraComponent)
}

RTTR_REGISTRATION
{
    using namespace Yumi;
    
    rttr::registration::class_<CameraComponent>("CameraComponent")
        .constructor<>()
        .property("Size", &CameraComponent::Size)
        .property("NearPlane", &CameraComponent::NearPlane)
        .property("FarPlane", &CameraComponent::FarPlane)
        .property("ProjectionMatrix", &CameraComponent::ProjectionMatrix)
        .property("ViewMatrix", &CameraComponent::ViewMatrix);

    ComponentReflection::RegisterComponentType<CameraComponent>();
}

namespace Yumi
{
    void CameraStatics::UpdateCameraMatrices(Actor& actor)
    {
        CameraComponent& camera = actor.Get<CameraComponent>();
        const Window& window = GetEngine().GetWindow();
        camera.ProjectionMatrix = Matrix4::OrthoProjection(window.GetAspect(), camera.Size, camera.NearPlane, camera.FarPlane);
        camera.ViewMatrix = Matrix4::ViewProjection(actor.GetTransform().Position, actor.GetTransform().Rotation);
    }
    
    Vector3 CameraStatics::ScreenToWorldPoint(Actor& actor, const Vector2& screenPoint)
    {
        const Engine& engine = Engine::GetInstance();
        const Window& window = GetEngine().GetWindow();
        CameraComponent& cameraComponent = actor.Get<CameraComponent>();
        return Math::ScreenToWorldPoint(cameraComponent.ProjectionMatrix * cameraComponent.ViewMatrix, screenPoint, window.GetSize());
    }
}