#include "SubTexture2D.h"
#include "Texture2D.h"

namespace Yumi
{
    SharedPtr<SubTexture2D> SubTexture2D::Create(const AssetRef& parentRef, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size)
    {
        return CreateSharedPtr<SubTexture2D>(parentRef, uvMin, uvMax, size);
    }

    SharedPtr<SubTexture2D> SubTexture2D::Create(const AssetRef& parentRef, const Vector2& locationInAtlas, const Vector2& size)
    {
        return CreateSharedPtr<SubTexture2D>(parentRef, locationInAtlas, size);
    }

    SubTexture2D::SubTexture2D(const AssetRef& parentRef, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size)
        : m_ParentRef(parentRef)
        , m_Size(size)
    {
        YCHECK(m_ParentRef.IsValid(), "SubTexture2D requires a valid parent!");
        SetUVCoords(uvMin, uvMax);
    }

    SubTexture2D::SubTexture2D(const AssetRef& parentTexture, const Vector2& locationInAtlas, const Vector2& size)
        : m_ParentRef(parentTexture)
        , m_Size(size)
    {
        YCHECK(parentTexture.IsValid(), "SubTexture2D requires a valid parent!");

        const Vector2 atlasSize = m_ParentRef.GetAs<Texture2D>().GetSize();
        const Vector2 uvMin((locationInAtlas.x * size.x) / atlasSize.x, (locationInAtlas.y * size.y) / atlasSize.y);
        const Vector2 uvMax(((locationInAtlas.x + 1) * size.x) / atlasSize.x, ((locationInAtlas.y + 1) * size.y) / atlasSize.y);
        SetUVCoords(uvMin, uvMax);
    }

    void SubTexture2D::SetUVCoords(const Vector2& uvMin, const Vector2& uvMax)
    {
        m_VertexUV[0] = { uvMin.x, uvMin.y }; // bottom-left
        m_VertexUV[1] = { uvMax.x, uvMin.y }; // bottom-right
        m_VertexUV[2] = { uvMax.x, uvMax.y }; // top-right
        m_VertexUV[3] = { uvMin.x, uvMax.y }; // top-left
    }
}