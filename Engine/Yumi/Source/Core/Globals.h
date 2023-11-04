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

    String GetWorkingDirectory();
    String GetAssetsFolderName();

    enum class RenderTarget
    {
        Default, FrameBuffer
    };

    namespace Graphics
    {
        const String GetSpriteShaderName();
        const Array<Vector2, 4>& GetDefaultSpriteUVs();
        const Array<Vector3, 4>& GetDefaultSpriteVertexPositions();
        void CalculateSpriteVertexPositions(const Vector2& textureSize, const Vector2& spriteSize, Array<Vector3, 4>& vertexPositions);
    }
}