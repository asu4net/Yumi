#include "Animation.h"
#include "Core/Engine.h"
#include "Asset/AssetManager.h"
#include "Rendering/Sprite.h"
#include "Rendering/SubTexture2D.h"

RTTR_REGISTRATION
{
    using namespace Yumi;
     rttr::registration::class_<Animation::Key>("Key")
        .constructor<>()
        .property("Key", &Animation::Key::KeyAssetRef)
        .property("KeyTime", &Animation::Key::KeyTime);

    rttr::registration::class_<Animation>("Animation")
        .constructor<>()
        .property("Keys", &Animation::m_Keys);
}

namespace Yumi
{
    YFORCE_LINK_IMPL(Animation)

    void Animation::PushKeysFromAtlas(const AssetRef& animationRef, const AssetRef& textureAtlasRef,
        const Vector2& atlasTileSize, const DynamicArray<Vector2>& atlasLocations, const DynamicArray<float>& keyTimes)
    {
        YCHECK(animationRef.IsValid(), "Animation should be valid");
        YCHECK(textureAtlasRef.IsValid(), "Sprite atlas should be valid");
        YCHECK(atlasLocations.size() == keyTimes.size(), "atlasLocations, keyTimes missmatch")
        
        AssetManager& assetManager = GetAssetManager();
        const String textureAtlasName = textureAtlasRef.GetPtr().lock()->GetAssetData().Name;
        Animation& animation = animationRef.GetAs<Animation>();

        for (uint32_t i = 0; i < atlasLocations.size(); ++i)
        {
            const Vector2& location = atlasLocations[i];
            const String subTextureName = textureAtlasName + "[" + std::to_string(i) + "]";
            const String subSpriteName = subTextureName + " [Sprite]";

            AssetRef spriteRef = assetManager.GetAssetByName(subSpriteName);

            if (!spriteRef.IsValid())
            {
                AssetRef subTextureRef = assetManager.GetAssetByName(subTextureName);

                if (!subTextureRef.IsValid())
                {
                    subTextureRef = assetManager.CreateAsset<SubTexture2D>(subTextureName, textureAtlasRef, location, atlasTileSize);
                }
                
                spriteRef = assetManager.CreateAsset<Sprite>(subSpriteName, subTextureRef, true);
            }
            animation.PushKey({spriteRef, keyTimes[i]});
        }

        animation.AdjustTime();
    }

    void Animation::PushKeysFromAtlas(const AssetRef& animationRef, const AssetRef& spriteAtlasRef, 
        const Vector2& atlasTileSize, uint32_t numOfTiles, float keyTime, bool atlasIsHorizontal)
    {
        DynamicArray<Vector2> atlasLocations(numOfTiles);
        DynamicArray<float> keyTimes(numOfTiles);

        float currentKeyTime = keyTime;

        for (uint32_t i = 0; i < numOfTiles; ++i)
        {
            keyTimes[i] = currentKeyTime;
            currentKeyTime += keyTime;

            Vector2 tileLocation = { (float)i, 0.f };

            if (!atlasIsHorizontal)
            {
                tileLocation = { 0.f, (float)i };
            }

            atlasLocations[i] = tileLocation;
        }

        PushKeysFromAtlas(animationRef, spriteAtlasRef, atlasTileSize,
            atlasLocations, keyTimes);
    }

    void Animation::PushKeysFromAtlas(const String& animationName, const String& atlasName, 
        const Vector2& atlasTileSize, uint32_t numOfTiles, float keyTime, bool atlasIsHorizontal)
    {
        AssetManager& assetManager = GetAssetManager();
        AssetRef animationRef = assetManager.GetAssetByName(animationName);
        AssetRef atlasRef = assetManager.GetAssetByName(atlasName);
        PushKeysFromAtlas(animationRef, atlasRef, atlasTileSize, numOfTiles, keyTime, atlasIsHorizontal);
    }

    void Animation::PostLoad()
    {
        for (Key& key : m_Keys)
        {
            key.KeyAssetRef.Retarget();
        }
    }

    void Animation::PushKey(const Key& key)
    {
        //YCHECK((key.KeyTime <= m_Time), "The KeyTime should be minor than the animation time");
        m_Keys.emplace_back(key);
        SortKeys();
    }

    void Animation::PopKey(uint32_t index)
    {
        m_Keys.erase(m_Keys.begin() + index);
        SortKeys();
    }

    const Animation::Key& Animation::GetKey(uint32_t index) const
    {
        return m_Keys[index];
    }

    size_t Animation::GetSize() const
    {
        return m_Keys.size();
    }

    void Animation::AdjustTime()
    {
        if (m_Keys.empty())
        {
            return;
        }

        DynamicArray<Key> keys(m_Keys.size());
        keys = m_Keys;
        
        std::sort(keys.begin(), keys.end(), [](const Key& a, const Key& b) {
            return a.KeyTime > b.KeyTime;
        });

        m_Time = keys[0].KeyTime;
    }

    void Animation::Clear()
    {
        m_Keys.clear();
    }

    void Animation::SortKeys()
    {
        std::sort(m_Keys.begin(), m_Keys.end(), [](const Key& a, const Key& b) {
            return a.KeyTime < b.KeyTime;
        });
    }
}