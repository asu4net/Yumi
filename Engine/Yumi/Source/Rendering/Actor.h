#pragma once

namespace Yumi
{
    class Actor
    {
    public:
        Actor() = default;
        Actor(const entt::entity entity, const WeakPtr<entt::registry>& registry)
            : m_Entity(entity)
            , m_Registry(registry)
        {}

        Actor(const Actor& other) = default;

        entt::entity GetEntity() const { return m_Entity; }

        bool operator==(const Actor& other)
        {
            return m_Entity == other.m_Entity;
        }

        void Reset()
        {
            m_Entity = entt::null;
            m_Registry.reset();
        }

        bool IsValid() const
        {
            if (m_Registry.expired())
                return false;
            return m_Registry.lock()->valid(m_Entity);
        }

        template<typename T>
        bool Has() const
        {
            YCHECK(IsValid(), "Invalid Actor!");
            return m_Registry.lock()->try_get<T>(m_Entity);
        }

        template<typename T, typename... Args>
        T& Add(Args&&... args) const
        {
            YCHECK(IsValid(), "Invalid Actor!");
            YCHECK(!Has<T>(), "Actor already has this component!");
            T& component = m_Registry.lock()->emplace<T>(m_Entity, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& Get() const
        {
            YCHECK(IsValid(), "Invalid Actor!");
            return m_Registry.lock()->get<T>(m_Entity);
        }

        template<typename T>
        void Remove() const
        {
            // Check with strings if type is transform o information component
            YCHECK(IsValid(), "Invalid Actor!");
            m_Registry.lock()->erase<T>(m_Entity);
        }

    private:
        entt::entity m_Entity = entt::null;
        WeakPtr<entt::registry> m_Registry;
    };
}