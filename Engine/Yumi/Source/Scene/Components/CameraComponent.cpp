#include "CameraComponent.h"
#include "TransformComponent.h"
#include "Scene\Actor.h"
#include "Window\Window.h"
#include "Core\Engine.h"

namespace Yumi
{
    void CameraStatics::UpdateCameraMatrices(Actor& actor)
    {
        CameraComponent& camera = actor.Get<CameraComponent>();
        const UniquePtr<Window>& window = GetEngine().GetWindow();
        camera.ProjectionMatrix = Matrix4::OrthoProjection(window->GetAspect(), camera.Size, camera.NearPlane, camera.FarPlane);
        camera.ViewMatrix = Matrix4::ViewProjection(actor.GetTransform().Position, actor.GetTransform().Rotation);
    }
    
    Vector3 CameraStatics::ScreenToWorldPoint(Actor& actor, const Vector2& screenPoint)
    {
        const Engine& engine = Engine::GetInstance();
        const UniquePtr<Window>& window = GetEngine().GetWindow();
        CameraComponent& cameraComponent = actor.Get<CameraComponent>();
        return Math::ScreenToWorldPoint(cameraComponent.ProjectionMatrix * cameraComponent.ViewMatrix, screenPoint, window->GetSize());
    }
}