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

    void CameraSystem::SetMainCameraActor(Actor actor)
    {
        YCHECK(actor.Has<CameraComponent>(), "Main camera actor should use have a CameraComponent");
        m_MainCameraActor = actor;
    }

    void CameraSystem::OnUpdate()
    {
        const auto view = GetRegistry().view<TransformComponent, CameraComponent>();
                
        view.each([&](entt::entity entity, TransformComponent&, CameraComponent& cameraComponent) {
            
            Actor actor = GetActorFromEntity(entity);
            CameraStatics::UpdateCameraMatrices(GetActorFromEntity(entity));
        });
         
        YCHECK(m_MainCameraActor.IsValid(), "MainCameraActor actor not assigned!");
        m_MainCameraActor = GetActorFromEntity(view.front());
        const CameraComponent& mainCamera = m_MainCameraActor.Get<CameraComponent>();
        Renderer::GetInstance().SetProjectionViewMatrix(mainCamera.ProjectionMatrix * mainCamera.ViewMatrix);
    }
}