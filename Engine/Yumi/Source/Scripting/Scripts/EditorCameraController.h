#pragma once
#include "Scripting/Script.h"

namespace Yumi
{
    class EditorCameraController : public Script
    {
        YSCRIPT_EXECUTION_CONTEXT(Editor)
    public:
        float MoveSpeed = 2.f;
        float RotationSpeed = 15.f;
        float ZoomStep = 0.25f;
        bool CanMove = true;

        void OnUpdate();

    private:
        void UpdateCameraPosition();
        
        Vector3 m_AuxPosition;
        Matrix4 m_AuxCameraMatrix;
        bool m_bMouseDown = false;
        Vector3 m_Offset;
    };
}