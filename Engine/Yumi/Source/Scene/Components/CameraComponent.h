#pragma once

namespace Yumi
{
    struct CameraComponent
    {
        float Size = 1.f;
        float NearPlane = 0.f;
        float FarPlane = 1000.f;
        Matrix4 ProjectionMatrix;
        Matrix4 ViewMatrix;
    };

    class Actor;

    struct CameraStatics 
    {
        static void UpdateCameraMatrices(Actor& actor);
        static Vector3 ScreenToWorldPoint(Actor& actor, const Vector2& screenPoint);
    };
}