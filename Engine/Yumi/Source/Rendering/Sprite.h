#pragma once
#include "Asset\AssetRef.h"
#include "Asset\Asset.h"

namespace Yumi
{
    class RendererTexture2D;
    class SubTexture2D;

    class Sprite : public Asset
    {
    public:
        Sprite() = default;
        Sprite(AssetRef textureRef, bool isSubTexture = false);
        Sprite(const String& textureAssetName, bool isSubTexture = false);

        bool Load() override { return true; }
        void Unload() override {}
        
        void Init(const AssetRef& textureRef, bool isSubTexture);
        void InitFromTexture(const AssetRef& textureRef);
        void InitFromSubTexture(const AssetRef& subTextureRef);
        
        const AssetRef& GetTextureRef() const { return m_TextureRef; }
        const AssetRef& GetSubTextureRef() const { return m_SubTextureRef; }
        const Array<Vector3, 4>& GetVertexPositions() const { return m_VertexPositions; }
        const Array<Vector2, 4>& GetVertexUVs() const { return m_VertexUVs; }

    private:
        AssetRef m_TextureRef;
        AssetRef m_SubTextureRef;

        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUVs;
    
        RTTR_ENABLE(Asset)
        RTTR_REGISTRATION_FRIEND
    };

    YFORCE_LINK(Sprite)
}