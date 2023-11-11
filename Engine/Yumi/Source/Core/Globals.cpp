#include "Globals.h"
#include "Engine.h"
#include "Time.h"
#include "Input/Input.h"
#include "Asset/AssetManager.h"

namespace Yumi
{
    Engine& CreateEngine()
    {
        return Engine::CreateInstance();
    }

    void DestroyEngine()
    {
        Engine::DestroyInstance();
    }

    Engine& GetEngine()
    {
        return Engine::GetInstance();
    }

    Time& GetTime()
    {
        return Time::GetInstance();
    }

    float GetDeltaTime()
    {
        return GetTime().DeltaTime();
    }

    Input& GetInput()
    {
        return Input::GetInstance();
    }

    AssetManager& GetAssetManager()
    {
        return AssetManager::GetInstance();
    }

    String GetWorkingDirectory()
    {
        static String workingDirectory;
        if (workingDirectory.empty())
        {
            char buffer[MAX_PATH];
            GetModuleFileNameA(nullptr, buffer, MAX_PATH);
            const String::size_type pos = String(buffer).find_last_of("\\/");
            workingDirectory = String(buffer).substr(0, pos);
        }
        return workingDirectory;
    }

    Yumi::String GetAssetsFolderName()
    {
        static const String s_AssetFolderName = "Assets";
        return s_AssetFolderName;
    }

    namespace Math
    {
        Vector3 ScreenToWorldPoint(const Matrix4& ProjectionViewMatrix, const Vector2& screenPoint, const Vector2& windowSize)
        {
            const float halfScreenWidth = windowSize.x / 2.f;
            const float halfScreenHeight = windowSize.y / 2.f;
            const Matrix4 inverseMv = ProjectionViewMatrix.GetInverse();
            const float nearPlaneX = (screenPoint.x - halfScreenWidth) / halfScreenWidth;
            const float nearPlaneY = -((screenPoint.y - halfScreenHeight) / halfScreenHeight);
            const Vector4 nearPlane = { nearPlaneX, nearPlaneY, -1, 1};
            Vector4 nearResult = inverseMv * nearPlane;
            nearResult /= nearResult.w;
            return { nearResult.x, nearResult.y, 0 };
        }
    }

    namespace Graphics
    {

        const String GetSpriteShaderName()
        {
            static const String spriteShaderName = "Sprite.glsl";
            return spriteShaderName;
        }

        const Array<Vector2, 4>& GetDefaultSpriteUVs()
        {
            static Array<Vector2, 4> uv =
            {
                Vector2(0, 0), // bottom-left
                Vector2(1, 0), // bottom-right
                Vector2(1, 1), // top-right
                Vector2(0, 1), // top-left
            };
            return uv;
        }

        const Array<Vector3, 4>& GetDefaultSpriteVertexPositions()
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

        void CalculateSpriteVertexPositions(const Vector2& textureSize, Array<Vector3, 4>& vertexPositions)
        {
            static Vector2 s_VertexMag = Vector2::One / 2;
            Vector2 pos = s_VertexMag;

            if (std::abs(textureSize.x - textureSize.y) > 0.0001f)
                pos = textureSize.Normalized() / 2;

            vertexPositions[0] = { -pos.x, -pos.y, 0 };
            vertexPositions[1] = {  pos.x, -pos.y, 0 };
            vertexPositions[2] = {  pos.x,  pos.y, 0 };
            vertexPositions[3] = { -pos.x,  pos.y, 0 };
        }

        void FlipVertexUVs(Flip flip, Array<Vector2, 4>& vertexUVs)
        {
            if (flip == Flip::None)
                return;

            Array<Vector2, 4> uv = vertexUVs;

            switch (flip)
            {
            case Flip::X:
                vertexUVs[0] = uv[1];
                vertexUVs[1] = uv[0];
                vertexUVs[2] = uv[3];
                vertexUVs[3] = uv[2];
                return;
            case Flip::Y:
                vertexUVs[0] = uv[2];
                vertexUVs[1] = uv[3];
                vertexUVs[2] = uv[0];
                vertexUVs[3] = uv[1];
                return;
            case Flip::Both:
                vertexUVs[0] = uv[3];
                vertexUVs[1] = uv[2];
                vertexUVs[2] = uv[1];
                vertexUVs[3] = uv[0];
            }
        }
    }
}