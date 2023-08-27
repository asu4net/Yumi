#include "Id.h"

namespace Yumi
{
    //Idk wtf is this, but it generates a random number.
    static std::random_device g_RandomDevice;
    static std::mt19937_64 g_RandomEngine(g_RandomDevice());
    static std::uniform_int_distribution<uint64_t> g_Distribution(g_RandomDevice());
    
    Id::Id()
        : m_IdHandler(g_Distribution(g_RandomEngine))
    {
    }

    Id::Id(const uint64_t id)
        : m_IdHandler(id)
    {
    }

    bool Id::operator==(const Id& other) const
    {
        return m_IdHandler == other.m_IdHandler;
    }

    bool Id::operator!=(const Id& other) const
    {
        return m_IdHandler != other.m_IdHandler;
    }
}