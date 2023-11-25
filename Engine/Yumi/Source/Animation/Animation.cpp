#include "Animation.h"
#include "Core/Engine.h"
#include "Asset/AssetManager.h"

namespace Yumi
{
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
                        
            AssetRef spriteRef = assetManager.GetAssetByName(subTextureName + " [Sprite]");

            if (!spriteRef.IsValid())
            {
                AssetRef subTextureRef = assetManager.GetAssetByName(subTextureName);

                if (!subTextureRef.IsValid())
                {
                    assetManager.CreateSubTextureAsset(AssetData{ subTextureName }, 
                        textureAtlasRef, location, atlasTileSize);
                }

                spriteRef = assetManager.CreateSpriteAsset(subTextureName);
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

    Animation::Animation(AssetRef* target)
        : m_Target(target)
    {
    }

    void Animation::SetTarget(AssetRef* target)
    {
        m_Target = target;
    }

    void Animation::Play()
    {
        m_IsPlaying = true;
    }

    void Animation::Pause()
    {
        m_IsPlaying = false;
    }

    void Animation::Stop()
    {
        Reset();
        m_IsPlaying = false;
    }

    void Animation::Reset()
    {
        m_CurrentTime = 0;
        m_CurrentIndex = 0;
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

    Animation::Key& Animation::GetKey(uint32_t index)
    {
        return m_Keys[index];
    }

    void Animation::AdjustTime()
    {
        if (m_Keys.empty())
        {
            return;
        }

        if (m_IsPlaying)
        {
            Stop();
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

    void Animation::Update()
    {
        YCHECK(!m_Keys.empty(), "There are no keys!");
        
        if (!m_IsPlaying)
        {
            return;
        }

        m_CurrentTime += GetDeltaTime();

        if (m_CurrentTime >= m_Keys[m_CurrentIndex].KeyTime)
        {
            *m_Target = m_Keys[m_CurrentIndex].KeyAssetRef;
            m_CurrentIndex++;
        }

        if (m_CurrentIndex == m_Keys.size())
        {
            if (m_LoopEnabled)
            {
                Reset();
            }
            else
            {
                Stop();
            }
        }
    }

    void Animation::SortKeys()
    {
        std::sort(m_Keys.begin(), m_Keys.end(), [](const Key& a, const Key& b) {
            return a.KeyTime < b.KeyTime;
        });
    }
}