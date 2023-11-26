#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"
#include "Core\Engine.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
    const Array<Vector2, 4>& Sprite::GetDefaultSpriteUVs()
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

    const Array<Vector3, 4>& Sprite::GetDefaultSpriteVertexPositions()
    {
        static Array<Vector3, 4> vertexPositions =
        {
            Vector3(-.5f, -.5f, 0),
            Vector3(.5f, -.5f, 0),
            Vector3(.5f,  .5f, 0),
            Vector3(-.5f,  .5f, 0)
        };
        return vertexPositions;
    }

    void Sprite::CalculateSpriteVertexPositions(const Vector2& textureSize, Array<Vector3, 4>& vertexPositions)
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

    void Sprite::FlipVertexUVs(Flip flip, Array<Vector2, 4>& vertexUVs)
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

    Sprite::Sprite(AssetRef textureRef, bool isSubTexture /*= false*/)
    {
        Init(textureRef, isSubTexture);
    }

    Sprite::Sprite(const String& textureAssetName, bool isSubTexture /*= false*/)
    {
        AssetRef textureRef = GetAssetManager().GetAssetByName(textureAssetName);
        Init(textureRef, isSubTexture);
    }

    void Sprite::Init(const AssetRef& textureRef, bool isSubTexture)
    {
        if (!isSubTexture)
        {
            InitFromTexture(textureRef);
            return;
        }

        InitFromSubTexture(textureRef);
    }

    void Sprite::InitFromTexture(const AssetRef& textureRef)
    {
        YCHECK(textureRef.IsValid(), "A valid Texture2D is required!");
        m_TextureRef = textureRef;
        CalculateSpriteVertexPositions(m_TextureRef.GetAs<Texture2D>().GetSize(), m_VertexPositions);
        m_VertexUVs = GetDefaultSpriteUVs();
    }

    void Sprite::InitFromSubTexture(const AssetRef& subTextureRef)
    {
        YCHECK(subTextureRef.IsValid(), "A valid SubTexture is required!");
        m_SubTextureRef = subTextureRef;
        SubTexture2D& subTexture = m_SubTextureRef.GetAs<SubTexture2D>();
        m_TextureRef = subTexture.GetParentRef();

        YCHECK(m_TextureRef.IsValid(), "Missing parent in SubTexture!");
        CalculateSpriteVertexPositions(subTexture.GetSize(), m_VertexPositions);
        m_VertexUVs = subTexture.GetVertexUV();
    }
}