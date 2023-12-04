#pragma once
#include <RTTR/registration_friend.h>
#include <RTTR/registration>
#include <RTTR/type>

namespace Yumi
{
    using Type = rttr::type;
    using Instance = rttr::instance;
    
    class Actor;

    using FnHas       = Delegate<bool(const Actor&)>;
    using FnGetByCopy = Delegate<Instance(const Actor&)>;
    using FnAdd       = Delegate<void(Actor&, const Instance&)>;
    using FnRemove    = Delegate<void(Actor&)>;
    using FnSet       = Delegate<void(Actor&, const Instance&)>;

    class ComponentType
    {
    public:
        ComponentType(Type type, const FnHas& hasFunction, const FnGetByCopy& getByCopyFunction, 
            const FnAdd& addFunction, const FnRemove& removeFunction, const FnSet& setFunction);

        Type GetType() const { return m_Type; }

        bool HasComponent(const Actor& actor);
        Instance GetComponentByCopy(const Actor& actor);
        void AddComponent(Actor& actor, const Instance& instance);
        void RemoveComponent(Actor& actor);
        void SetComponentData(Actor& actor, const Instance& instance);

    private:
        Type m_Type;
        FnHas m_HasFunction;
        FnGetByCopy m_GetByCopyFunction;
        FnAdd m_AddFunction;
        FnRemove m_RemoveFunction;
        FnSet m_SetFunction;
    };

    class ComponentReflection
    {
    public:
        template<typename T>
        static void RegisterComponentType()
        {
            Type type = Type::get<T>();
            SharedPtr<ComponentType> componentType = CreateSharedPtr<ComponentType>(
                type,
                FnHas([](const Actor& actor) -> bool { return actor.Has<T>(); }),
                FnGetByCopy([](const Actor& actor) -> Instance { return actor.Get<T>(); }),
                FnAdd([](Actor& actor, const Instance& instance) -> void { actor.Add<T>(*instance.try_convert<T>()); }),
                FnRemove([](Actor& actor) -> void { return actor.Remove<T>(); }),
                FnSet([](Actor& actor, const Instance& instance) -> void { actor.Get<T>() = *instance.try_convert<T>(); })
            );
            m_Components[type] = componentType;
        }
        
        static const SharedPtr<ComponentType>& GetComponentOfType(Type type);

    private:
        inline static Map<Type, SharedPtr<ComponentType>> m_Components;
    };
}

// Try to send to your graphic API an element with a vtable pointer and see what happens
#define RTTR_ENABLE_NO_VIRTUAL \
public:\
RTTR_BEGIN_DISABLE_OVERRIDE_WARNING \
    RTTR_INLINE ::rttr::type get_type() const { return ::rttr::detail::get_type_from_instance(this); }  \
    RTTR_INLINE void* get_ptr() { return reinterpret_cast<void*>(this); } \
    RTTR_INLINE ::rttr::detail::derived_info get_derived_info() { return {reinterpret_cast<void*>(this), ::rttr::detail::get_type_from_instance(this)}; } \
RTTR_END_DISABLE_OVERRIDE_WARNING \
private: