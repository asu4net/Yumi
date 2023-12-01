#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"
#include "Core\Engine.h"
#include "Asset\AssetManager.h"

namespace Yumi
{
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
        Math::CalculateQuadVertexPositions(m_TextureRef.GetAs<Texture2D>().GetSize(), m_VertexPositions);
        m_VertexUVs = Math::GetDefaultQuadUVs();
    }

    void Sprite::InitFromSubTexture(const AssetRef& subTextureRef)
    {
        YCHECK(subTextureRef.IsValid(), "A valid SubTexture is required!");
        m_SubTextureRef = subTextureRef;
        SubTexture2D& subTexture = m_SubTextureRef.GetAs<SubTexture2D>();
        m_TextureRef = subTexture.GetParentRef();

        YCHECK(m_TextureRef.IsValid(), "Missing parent in SubTexture!");
        Math::CalculateQuadVertexPositions(subTexture.GetSize(), m_VertexPositions);
        m_VertexUVs = subTexture.GetVertexUV();
    }
}