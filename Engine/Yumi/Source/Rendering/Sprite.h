#pragma once
#include "Asset\AssetRef.h"
#include "Asset\Asset.h"

namespace Yumi
{
    class Texture2D;
    class SubTexture2D;

    class Sprite : public Asset
    {
    public:
        static SharedPtr<Sprite> Create(const AssetRef& textureRef);
        static SharedPtr<Sprite> CreateFromTexture(const AssetRef& textureRef);
        static SharedPtr<Sprite> CreateFromSubTexture(const AssetRef& subTextureRef);
        static const Array<Vector2, 4>& GetDefaultSpriteUVs();
        static const Array<Vector3, 4>& GetDefaultSpriteVertexPositions();
        static void CalculateSpriteVertexPositions(const Vector2& textureSize, Array<Vector3, 4>& vertexPositions);
        static void FlipVertexUVs(Flip flip, Array<Vector2, 4>& vertexUVs);

        Sprite() = default;
                
        bool Load() override;
        void Unload() override;

        AssetData GetAssetData() const override { return m_AssetData; };
        
        const AssetRef& GetTextureRef() const { return m_TextureRef; }
        const AssetRef& GetSubTextureRef() const { return m_SubTextureRef; }
        const Array<Vector3, 4>& GetVertexPositions() const { return m_VertexPositions; }
        const Array<Vector2, 4>& GetVertexUVs() const { return m_VertexUVs; }

    private:
        virtual void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; };
        
        AssetData m_AssetData;
        AssetRef m_TextureRef;
        AssetRef m_SubTextureRef;

        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUVs;

        friend class AssetManager;
    };
}