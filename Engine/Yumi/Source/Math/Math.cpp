#include "Math.h"

namespace Yumi::Math
{
    Vector3 ScreenToWorldPoint(const Matrix4& ProjectionViewMatrix, const Vector2& screenPoint, const Vector2& windowSize)
    {
        const float halfScreenWidth = windowSize.x / 2.f;
        const float halfScreenHeight = windowSize.y / 2.f;
        const Matrix4 inverseMv = ProjectionViewMatrix.GetInverse();
        const float nearPlaneX = (screenPoint.x - halfScreenWidth) / halfScreenWidth;
        const float nearPlaneY = -((screenPoint.y - halfScreenHeight) / halfScreenHeight);
        const Vector4 nearPlane = { nearPlaneX, nearPlaneY, -1, 1 };
        Vector4 nearResult = inverseMv * nearPlane;
        nearResult /= nearResult.w;
        return { nearResult.x, nearResult.y, 0 };
    }

    const Array<Vector2, 4>& Math::GetDefaultSpriteUVs()
    {
        static Array<Vector2, 4> uv =
        {
            Vector2(0, 0), // bottom-left
            Vector2(1, 0), // bottom-right
            Vector2(1, 1), // top-right
            Vector2(0, 1)  // top-left
        };
        return uv;
    }

    const Array<Vector3, 4>& Math::GetDefaultSpriteVertexPositions()
    {
        static Array<Vector3, 4> vertexPositions =
        {
            Vector3(-.5f, -.5f, 0),
            Vector3( .5f, -.5f, 0),
            Vector3( .5f,  .5f, 0),
            Vector3(-.5f,  .5f, 0)
        };
        return vertexPositions;
    }
}