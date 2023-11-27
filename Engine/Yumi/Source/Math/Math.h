#pragma once

namespace Yumi::Math
{
    inline float FloatMax() { return std::numeric_limits<float>::max(); }
    Vector3 ScreenToWorldPoint(const Matrix4& ProjectionViewMatrix, const Vector2& screenPoint, const Vector2& windowSize);
    const Array<Vector2, 4>& GetDefaultSpriteUVs();
    const Array<Vector3, 4>& GetDefaultSpriteVertexPositions();
}