#pragma once

namespace Yumi::Math
{
    inline float FloatMax() { return std::numeric_limits<float>::max(); }
    Vector3 ScreenToWorldPoint(const Matrix4& ProjectionViewMatrix, const Vector2& screenPoint, const Vector2& windowSize);

    // Quad
    const Array<Vector2, 4>& GetDefaultQuadUVs();
    const Array<Vector3, 4>& GetDefaultQuadVertexPositions();
    void CalculateQuadVertexPositions(const Vector2& textureSize, Array<Vector3, 4>& vertexPositions);
    void FlipQuadVertexUVs(Flip flip, Array<Vector2, 4>& vertexUVs);
}