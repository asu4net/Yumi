#include "Animation.h"
#include "Core/Engine.h"

namespace Yumi
{
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
        m_Keys.emplace_back(key);
        SortKeys();
    }

    void Animation::PopKey(uint32_t index)
    {
        m_Keys.erase(m_Keys.begin() + index);
        SortKeys();
    }

    void Animation::Clear()
    {
        m_Keys.clear();
    }

    void Animation::Update()
    {
        if (m_Keys.empty() || m_Target.expired() || !m_IsPlaying)
            return;
        
        m_CurrentTime += GetDeltaTime();

        if (m_CurrentTime >= m_Keys[m_CurrentIndex].KeyTime)
        {
            AssetRef* assetRef = m_Target.lock().get();
            *assetRef = m_Keys[m_CurrentIndex].KeyAssetRef;
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