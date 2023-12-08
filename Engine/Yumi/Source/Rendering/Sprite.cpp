#include "Sprite.h"
#include "Core/Engine.h"
#include "Rendering/Renderer.h"
#include "RendererTexture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <GLAD/glad.h>

RTTR_REGISTRATION
{
    using namespace Yumi;

    rttr::registration::class_<SubSprite>("SubSprite")
        .constructor<>()
        (
            rttr::policy::ctor::as_object
        )
        .property("Size", &SubSprite::Size)
        .property("VertexPositions", &SubSprite::VertexPositions)
        .property("VertexUVs", &SubSprite::VertexUVs);

    rttr::registration::class_<Sprite>("Sprite")
        .constructor<>()
        .property("MagFilter", &Sprite::m_MagFilter)
        .property("MinFilter", &Sprite::m_MinFilter)
        .property("WrapModeU", &Sprite::m_WrapModeU)
        .property("WrapModeV", &Sprite::m_WrapModeV)
        .property("VertexPositions", &Sprite::m_VertexPositions)
        .property("VertexUVs", &Sprite::m_VertexUVs)
        .property("SubSprites", &Sprite::m_SubSprites);
}

namespace Yumi
{
    YFORCE_LINK_IMPL(Sprite)

    Sprite::Sprite() 
    {
        Init();
    };

    void Sprite::Init(const SpriteInitSettings& initSettings)
    {
        m_MagFilter = initSettings.magFilter;
        m_MinFilter = initSettings.minFilter;
        m_WrapModeU = initSettings.wrapModeU;
        m_WrapModeV = initSettings.wrapModeV;
    }

    bool Sprite::Load()
    {
        const String absolutePath = GetAssetData().AbsolutePath;
        if (absolutePath == AssetData::s_EmptyPathString) return true;

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        m_Data = stbi_load(absolutePath.c_str(), &width, &height, &channels, 0);

        if (!m_Data)
            return false;

        m_Size = { (float) width, (float) height };
        m_Channels = channels;

        Texture2DSettings settings;
        settings.Width = width;
        settings.Height = height;
        settings.Channels = m_Channels;
        settings.MagFilter = m_MagFilter;
        settings.MinFilter = m_MinFilter;
        settings.WrapModeU = m_WrapModeU;
        settings.WrapModeV = m_WrapModeV;

        m_RendererTextureId = GetRenderer().CreateTexture2D(settings, m_Data);

        Math::FillQuadVertexPositions(m_Size, m_VertexPositions);
        m_VertexUVs = Math::GetDefaultQuadUVs();

        return true;
    }
    
    void Sprite::Unload()
    {
        stbi_image_free(m_Data);
        m_Data = nullptr;
        GetRenderer().DestroyTexture2D(m_RendererTextureId);
    }
    
    const SubSprite& Sprite::PushSubSprite(const String& name, const Vector2& uvMin, const Vector2& uvMax, const Vector2& size)
    {
        YCHECK(!m_SubSprites.count(name), "Duplicated name found!");
        SubSprite subSprite;
        subSprite.Size = size;
        Math::FillQuadVertexPositions(size, subSprite.VertexPositions);
        Math::FillQuadVertexUVs(uvMin, uvMax, subSprite.VertexUVs);
        m_SubSprites[name] = subSprite;
        return m_SubSprites[name];
    }

    const SubSprite& Sprite::PushSubSprite(const String& name, const Vector2& locationInAtlas, const Vector2& size)
    {
        YCHECK(!m_SubSprites.count(name), "Duplicated name found!");
        SubSprite subSprite;
        subSprite.Size = size;
        const Vector2 uvMin((locationInAtlas.x * size.x)       / m_Size.x, (locationInAtlas.y * size.y)       / m_Size.y);
        const Vector2 uvMax(((locationInAtlas.x + 1) * size.x) / m_Size.x, ((locationInAtlas.y + 1) * size.y) / m_Size.y);
        Math::FillQuadVertexPositions(size, subSprite.VertexPositions);
        Math::FillQuadVertexUVs(uvMin, uvMax, subSprite.VertexUVs);
        m_SubSprites[name] = subSprite;
        return m_SubSprites[name];
    }

    void Sprite::PushSpriteSheet(const Vector2& atlasTileSize, uint32_t numOfTiles, bool atlasIsHorizontal)
    {
        for (uint32_t i = 0; i < numOfTiles; ++i)
        {
            Vector2 tileLocation = { (float) i, 0.f };

            if (!atlasIsHorizontal)
            {
                tileLocation = { 0.f, (float) i };
            }

            const String tileName = GetAssetData().Name + " [" + std::to_string(i) + "]";
            PushSubSprite(tileName, tileLocation, atlasTileSize);
        }
    }

    void Sprite::PopSubSprite(const String& name)
    {
        YCHECK(m_SubSprites.count(name), "There is not a SubSprite called %s!", name.c_str());
        m_SubSprites.erase(name);
    }

    const SubSprite& Sprite::GetSubSprite(const String& name)
    {
        YCHECK(m_SubSprites.count(name), "There is not a SubSprite called %s!", name.c_str());
        return m_SubSprites[name];
    }

    bool Sprite::ContainsSubSprite(const String& name)
    {
        return m_SubSprites.count(name);
    }

    void Sprite::ForEachSubSprite(Delegate<void(const String&, const SubSprite&)> eachDelegate)
    {
        for (const auto& [name, subSprite] : m_SubSprites)
        {
            eachDelegate(name, subSprite);
        }
    }
}