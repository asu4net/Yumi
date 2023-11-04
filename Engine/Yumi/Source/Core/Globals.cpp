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

        void CalculateSpriteVertexPositions(const Vector2& textureSize, const Vector2& spriteSize, Array<Vector3, 4>& vertexPositions)
        {
            static Vector2 s_VertexMag = Vector2::One / 2;
            Vector2 pos = s_VertexMag;

            if (std::abs(textureSize.x - textureSize.y) > 0.0001f)
                pos = textureSize.Normalized() / 2;

            pos.x *= spriteSize.x;
            pos.y *= spriteSize.y;

            vertexPositions[0] = { -pos.x, -pos.y, 0 };
            vertexPositions[1] = {  pos.x, -pos.y, 0 };
            vertexPositions[2] = {  pos.x,  pos.y, 0 };
            vertexPositions[3] = { -pos.x,  pos.y, 0 };
        }
    }
}