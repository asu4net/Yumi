#include "SubTexture2D.h"
#include "Texture2D.h"

namespace Yumi
{
    SharedPtr<SubTexture2D> SubTexture2D::Create(const AssetLink<Texture2D>& parentTexture, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size)
    {
        return CreateSharedPtr<SubTexture2D>(parentTexture, uvMin, uvMax, size);
    }

    SubTexture2D::SubTexture2D(const AssetLink<Texture2D>& parentTexture, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size)
        : m_ParentTexture(parentTexture)
        , m_Size(size)
    {
        YCHECK(m_ParentTexture.IsValid(), "SubTexture2D requires a valid parent!");

        const Vector2 atlasSize = m_ParentTexture->GetSize();

        m_VertexUV[0] = { uvMin.x, uvMin.y }; // bottom-left
        m_VertexUV[1] = { uvMax.x, uvMin.y }; // bottom-right
        m_VertexUV[2] = { uvMax.x, uvMax.y }; // top-right
        m_VertexUV[3] = { uvMin.x, uvMax.y }; // top-left
    }

    SharedPtr<SubTexture2D> SubTexture2D::CreateFromAtlasLocation(const AssetLink<Texture2D>& parentTexture, const Vector2& locationInAtlas, const Vector2& size)
    {
        YCHECK(parentTexture.IsValid(), "SubTexture2D requires a valid parent!");
        
        const Vector2 atlasSize = parentTexture->GetSize();
        const Vector2 uvMin((locationInAtlas.x * size.x) / atlasSize.x, (locationInAtlas.y * size.y) / atlasSize.y);
        const Vector2 uvMax(((locationInAtlas.x + 1) * size.x) / atlasSize.x, ((locationInAtlas.y + 1) * size.y) / atlasSize.y);
        return CreateSharedPtr<SubTexture2D>(parentTexture, uvMin, uvMax, size);
    }
}