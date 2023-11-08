#pragma once
#include "Asset\AssetLink.h"
#include "Asset\Asset.h"

namespace Yumi
{
    class Texture2D;
    class SubTexture2D;

    class Sprite : public Asset
    {
    public:
        Sprite() = default;
        Sprite(const AssetLink<Texture2D>& texture);
        Sprite(const AssetLink<SubTexture2D>& subTexture);
        
        bool Load() override;
        void Unload() override;

        AssetData GetAssetData() const override { return m_AssetData; };
        
        const AssetLink<Texture2D>& GetTexture() const { return m_Texture; }
        const AssetLink<SubTexture2D>& GetSubTexture() const { return m_SubTexture; }
        const Array<Vector3, 4>& GetVertexPositions() const { return m_VertexPositions; }
        const Array<Vector2, 4>& GetVertexUVs() const { return m_VertexUVs; }

    private:
        virtual void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; };
        
        AssetData m_AssetData;
        AssetLink<Texture2D> m_Texture;
        AssetLink<SubTexture2D> m_SubTexture;

        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUVs;

        friend class AssetManager;
    };
}