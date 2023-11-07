#pragma once
#include "Asset/Asset.h"
#include "Asset\AssetLink.h"

namespace Yumi
{
    class Texture2D;

    class SubTexture2D : public Asset
    {
    public:
        static SharedPtr<SubTexture2D> Create(const AssetLink<Texture2D>& parentTexture, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size);
        static SharedPtr<SubTexture2D> CreateFromAtlasLocation(const AssetLink<Texture2D>& parentTexture, const Vector2& locationInAtlas, const Vector2& size);

        SubTexture2D() = default;
        SubTexture2D(const AssetLink<Texture2D>& parentTexture, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size);

        AssetLink<Texture2D> GetParent() const { return m_ParentTexture; }
        const Array<Vector2, 4>& GetVertexUV() const { return m_VertexUV; }
        Vector2 GetSize() const { return m_Size; }

        bool Load() override { return true; }
        void Unload() override {};
        
        AssetData GetAssetData() const override { return m_AssetData; }

    private:
        AssetLink<Texture2D> m_ParentTexture;
        Array<Vector2, 4> m_VertexUV;
        Vector2 m_Size;
        AssetData m_AssetData;

        void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; }

        friend class AssetManager;
    };
}