#include "FreeLookCameraScript.h"
#include "Input\Input.h"
#include "Input\KeyCodes.h"
#include "Scene\Components\CameraComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Window\Window.h"
#include "Core\Engine.h"

namespace Yumi
{
    void FreeLookCameraScript::OnUpdate()
    {
        UpdateCameraPosition();
    }

    void FreeLookCameraScript::UpdateCameraPosition()
    {
        if (!CanMove)
            return;

        CameraComponent& camera = Get<CameraComponent>();
        Input& input = Input::GetInstance();
        const UniquePtr<Window>& window = GetEngine().GetWindow();

        const bool IsRightMousePressed = input.IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);
        
        // Mouse pressed
        if (!m_bMouseDown && IsRightMousePressed)
        {
            m_bMouseDown = true;
            m_Offset = Math::ScreenToWorldPoint(camera.ProjectionMatrix * camera.ViewMatrix, input.MousePosition(), window->GetSize()) + m_AuxPosition;
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
            m_AuxCameraMatrix = Matrix4::OrthoProjection(window->GetAspect(), camera.Size, camera.NearPlane, camera.FarPlane)
                * Matrix4::ViewProjection(m_AuxPosition, Vector3::Zero);

            const Vector2 mouseWorld = Math::ScreenToWorldPoint(m_AuxCameraMatrix, input.MousePosition(), window->GetSize());

            GetTransform().Position = Vector3(mouseWorld * -1, GetTransform().Position.z) + Vector3(m_Offset.x, m_Offset.y, 0);
        }
    }
}