#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

namespace Yumi
{
    Sprite::Sprite(const AssetLink<Texture2D>& texture)
        : m_Texture(texture)
    {
        YCHECK(texture.IsValid(), "A valid Texture2D is required!");
        Graphics::CalculateSpriteVertexPositions(m_Texture->GetSize(), m_VertexPositions);
        m_VertexUVs = Graphics::GetDefaultSpriteUVs();
    }

    Sprite::Sprite(const AssetLink<SubTexture2D>& subTexture)
        : m_Texture(subTexture->GetParent())
        , m_SubTexture(subTexture)
    {
        YCHECK(subTexture.IsValid(), "A valid SubTexture is required!");
        YCHECK(m_Texture.IsValid(), "Missing parent in subtexture!");
        Graphics::CalculateSpriteVertexPositions(m_SubTexture->GetSize(), m_VertexPositions);
        m_VertexUVs = m_SubTexture->GetVertexUV();
    }

    bool Sprite::Load()
    {
        return true;
    }

    void Sprite::Unload()
    {
    }
}