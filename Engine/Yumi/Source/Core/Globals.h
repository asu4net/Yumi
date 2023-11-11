#pragma once

namespace Yumi
{
    class Engine& CreateEngine();
    void DestroyEngine();

    Engine& GetEngine();
    class Time& GetTime();
    float GetDeltaTime();
    class Input& GetInput();
    class AssetManager& GetAssetManager();
    class World& GetWorld();
    class Renderer& GetRenderer();
    class Window& GetWindow();

    String GetWorkingDirectory();
    String GetAssetsFolderName();

    namespace Math
    {
        Vector3 ScreenToWorldPoint(const Matrix4& ProjectionViewMatrix, const Vector2& screenPoint, const Vector2& windowSize);
    }

    enum class GraphicsAPI
    {
        None, OpenGL
    };

    enum class RenderTarget
    {
        Default, FrameBuffer
    };

    enum class Flip
    {
        None, X, Y, Both
    };

    namespace Graphics
    {
        const String GetSpriteShaderName();
        const Array<Vector2, 4>& GetDefaultSpriteUVs();
        const Array<Vector3, 4>& GetDefaultSpriteVertexPositions();
        void CalculateSpriteVertexPositions(const Vector2& textureSize, Array<Vector3, 4>& vertexPositions);
        void FlipVertexUVs(Flip flip, Array<Vector2, 4>& vertexUVs);
    }
}