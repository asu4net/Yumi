#pragma once
#include "Asset/Asset.h"

namespace Yumi
{
    class Shader : public Asset
    {
    public:
        Shader() = default;

        AssetData GetAssetData() const override { return m_AssetData; }
        void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; }

        bool Load() override;
        void Unload() override;

    private:
        AssetData m_AssetData;
        Id m_RendererShaderId = 0;
        String m_VertexSource;
        String m_FragmentSource;

        bool ReadFromFile(const String& fileLocation, String& vertexSource, String& fragmentSource);
    };
}
