#include "FreeLookCameraScript.h"
#include "Input\Input.h"
#include "Input\KeyCodes.h"
#include "Scene\Components\CameraComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Window\Window.h"
#include "Core\Engine.h"

namespace Yumi
{
    void FreeLookCameraScript::OnStart()
    {
        auto& camera = Get<CameraComponent>();
        m_DesiredZoom = camera.Size;
        
        GetWindow().Events().ScrollEvent.Add([&](const Vector2& offset) {

            if (GetInput().IsConsumed()) return;
            
            m_DesiredZoom -= offset.y * ZoomStep;
            m_DesiredZoom = std::clamp(m_DesiredZoom, camera.NearPlane, Math::FloatMax());
        });
    }

    void FreeLookCameraScript::OnUpdate()
    {
        UpdateCameraZoom();
        UpdateCameraPosition();
    }

    void FreeLookCameraScript::UpdateCameraZoom()
    {
        auto& camera = Get<CameraComponent>();

        if (std::abs(m_DesiredZoom - camera.Size) > .01f)
        {
            const float dir = camera.Size < m_DesiredZoom ? 1.f : -1.f;
            camera.Size += ZoomSpeed * dir * GetDeltaTime();
        }
        else
        {
            camera.Size = m_DesiredZoom;
        }
    }

    void FreeLookCameraScript::UpdateCameraPosition()
    {
        if (!CanMove)
            return;

        CameraComponent& camera = Get<CameraComponent>();

        const bool IsRightMousePressed = GetInput().IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
        
        // Mouse pressed
        if (!m_bMouseDown && IsRightMousePressed)
        {
            m_bMouseDown = true;
            m_Offset = Math::ScreenToWorldPoint(camera.ProjectionMatrix * camera.ViewMatrix, GetInput().MousePosition(), GetWindow().GetSize()) + m_AuxPosition;
        }
        
        // Mouse released
        if (m_bMouseDown && !IsRightMousePressed)
        {
            m_bMouseDown = false;
            m_AuxPosition = GetTransform().Position;
        }
                
        // Mouse hold
        if (IsRightMousePressed)
        {
            m_AuxCameraMatrix = Matrix4::OrthoProjection(GetWindow().GetAspect(), camera.Size, camera.NearPlane, camera.FarPlane)
                * Matrix4::ViewProjection(m_AuxPosition, Vector3::Zero);

            const Vector2 mouseWorld = Math::ScreenToWorldPoint(m_AuxCameraMatrix, GetInput().MousePosition(), GetWindow().GetSize());

            GetTransform().Position = Vector3(mouseWorld * -1, GetTransform().Position.z) + Vector3(m_Offset.x, m_Offset.y, 0);
        }
    }
}