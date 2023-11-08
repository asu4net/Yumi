#pragma once
#include "Scene\Actor.h"

namespace Yumi
{
    struct TransformComponent
    {
        Vector3 Position;
        Vector3 Rotation;
        Vector3 Scale = Vector3::One;

        TransformComponent() = default;

        TransformComponent(const Vector3& position, const Vector3& rotation, const Vector3& scale)
            : Position(position)
            , Rotation(rotation)
            , Scale(scale)
        {
        }

        Matrix4 GetMatrix() { return Matrix4::CreateTransform(Position, Rotation, Scale); }
    };
}