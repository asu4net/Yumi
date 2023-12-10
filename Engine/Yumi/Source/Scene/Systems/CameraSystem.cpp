#include "CameraSystem.h"
#include "Scene\Components\CameraComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Rendering\Renderer.h"
#include "Core\Engine.h"

namespace Yumi
{

    CameraSystem::CameraSystem(Scene* scene)
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
        GetRenderer().SetProjectionViewMatrix(mainCamera.ProjectionMatrix * mainCamera.ViewMatrix);
    }
}