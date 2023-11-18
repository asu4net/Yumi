#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

namespace Yumi
{
    SharedPtr<Sprite> Sprite::Create(const AssetRef& textureRef)
    {
        SharedPtr<Asset> asset = textureRef.GetPtr().lock();
        if (asset->GetAssetData().AssetType == "Texture2D")
            return CreateFromTexture(textureRef);
        if (asset->GetAssetData().AssetType == "SubTexture2D")
            return CreateFromSubTexture(textureRef);
        YCHECK(false, "Invalid asset type");
        return nullptr;
    }

    SharedPtr<Sprite> Sprite::CreateFromTexture(const AssetRef& textureRef)
    {
        YCHECK(textureRef.IsValid(), "A valid Texture2D is required!");
        SharedPtr<Sprite> sprite = CreateSharedPtr<Sprite>();
        sprite->m_TextureRef = textureRef;
        Graphics::CalculateSpriteVertexPositions(sprite->m_TextureRef.GetAs<Texture2D>().GetSize(), sprite->m_VertexPositions);
        sprite->m_VertexUVs = Graphics::GetDefaultSpriteUVs();
        return sprite;
    }

    SharedPtr<Sprite> Sprite::CreateFromSubTexture(const AssetRef& subTextureRef)
    {
        YCHECK(subTextureRef.IsValid(), "A valid SubTexture is required!");
        SharedPtr<Sprite> sprite = CreateSharedPtr<Sprite>();
        sprite->m_SubTextureRef = subTextureRef;
        SubTexture2D& subTexture = sprite->m_SubTextureRef.GetAs<SubTexture2D>();
        sprite->m_TextureRef = subTexture.GetParentRef();
        YCHECK(sprite->m_TextureRef.IsValid(), "Missing parent in subtexture!");
        Graphics::CalculateSpriteVertexPositions(subTexture.GetSize(), sprite->m_VertexPositions);
        sprite->m_VertexUVs = subTexture.GetVertexUV();
        return sprite;
    }

    bool Sprite::Load()
    {
        return true;
    }

    void Sprite::Unload()
    {
    }
}