#pragma once

namespace Yumi
{
    class Id
    {
    public:
        Id();
        Id(uint64_t idHandler);

        explicit operator uint64_t() const { return m_IdHandler; }
        bool operator ==(const Id& other) const;
        bool operator !=(const Id& other) const;

        RTTR_ENABLE()
        RTTR_REGISTRATION_FRIEND

    private:
        uint64_t m_IdHandler;
    };
}

template <>
struct std::hash<Yumi::Id>
{
    std::size_t operator()(const Yumi::Id id) const noexcept
    {
        return hash<uint64_t>()(static_cast<uint64_t>(id));
    }
};
