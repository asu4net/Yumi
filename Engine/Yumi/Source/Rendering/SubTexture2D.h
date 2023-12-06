#pragma once
#include "Asset/Asset.h"
#include "Asset\AssetRef.h"

namespace Yumi
{
    class RendererTexture2D;

    class SubTexture2D : public Asset
    {
    public:
        SubTexture2D() = default;
        SubTexture2D(const AssetRef& parentTextureRef, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size);
        SubTexture2D(const AssetRef& parentTextureRef, const Vector2& locationInAtlas, const Vector2& size);

        void Init(const AssetRef& parentTextureRef, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size);
        void Init(const AssetRef& parentTextureRef, const Vector2& locationInAtlas, const Vector2& size);

        AssetRef GetParentRef() const { return m_ParentRef; }
        const Array<Vector2, 4>& GetVertexUV() const { return m_VertexUV; }
        Vector2 GetSize() const { return m_Size; }

        bool Load() override { return true; }
        void Unload() override {};
        
    private:
        AssetRef m_ParentRef;
        Array<Vector2, 4> m_VertexUV;
        Vector2 m_Size;

        void SetUVCoords(const Vector2& uvMin, const Vector2& uvMax);

        RTTR_ENABLE(Asset)
        RTTR_REGISTRATION_FRIEND
    };

    YFORCE_LINK(SubTexture2D)
}