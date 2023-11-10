#include "CameraSystem.h"
#include "..\Components\CameraComponent.h"
#include "Rendering\Renderer.h"
#include "..\Components\TransformComponent.h"

namespace Yumi
{

    CameraSystem::CameraSystem(const SharedPtr<Scene>& scene)
        : System(scene)
    {
    }

    void CameraSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<TransformComponent, CameraComponent>();

        GetRegistry().sort<CameraComponent>([](const CameraComponent& a, const CameraComponent& b) {
            return a.Priority > b.Priority;
        });
        
        view.each([&](entt::entity entity, TransformComponent&, CameraComponent&) {
            CameraStatics::UpdateCameraMatrices(GetActorFromEntity(entity));
        });

        m_MainCameraActor = GetActorFromEntity(view.front());
        const CameraComponent& mainCamera = m_MainCameraActor.Get<CameraComponent>();
        Renderer::GetInstance().SetProjectionViewMatrix(mainCamera.ProjectionMatrix * mainCamera.ViewMatrix);
    }
}