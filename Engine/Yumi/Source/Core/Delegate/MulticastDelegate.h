﻿#pragma once
#include "Delegate.h"

#define YDECLARE_EVENT(OwningType, EventName) \
class EventName : public Yumi::MulticastDelegate<void()> \
{ \
    void Broadcast() \
    { \
        operator()(); \
    } \
    friend OwningType; \
};

#define YDECLARE_EVENT_ONE_PARAM(OwningType, EventName, TypeOne, ParamOne) \
class EventName : public Yumi::MulticastDelegate<void(TypeOne)> \
{ \
    void Broadcast(TypeOne ParamOne) \
    { \
        operator()(ParamOne); \
    } \
    friend OwningType; \
};

#define YDECLARE_EVENT_TWO_PARAM(OwningType, EventName, TypeOne, ParamOne, TypeTwo, ParamTwo) \
class EventName : public Yumi::MulticastDelegate<void(TypeOne, TypeTwo)> \
{ \
    void Broadcast(TypeOne ParamOne, TypeTwo ParamTwo) \
    { \
        operator()(ParamOne, ParamTwo); \
    } \
    friend OwningType; \
};

namespace Yumi
{
    template<typename T>
    class MulticastDelegate;
    
    template<typename ...TArgs>
    class MulticastDelegate<void(TArgs...)>
    {
    public:
        MulticastDelegate() = default;
        
        void Add(const Delegate<void(TArgs...)>& delegate)
        {
            m_delegates.push_back(delegate);
        }

        void Add(const std::function<void(TArgs...)>& func)
        {
            m_delegates.push_back({func});
        }
        
        Delegate<void(TArgs...)> AddRaw(const std::function<void(TArgs...)>& function)
        {
            Delegate<void(TArgs...)> delegate = function;
            m_delegates.push_back(delegate);
            return delegate;
        }

        template<typename TSubscriber>
        Delegate<void(TArgs...)> AddRaw(TSubscriber* obj, void(TSubscriber::*funcPtr)(TArgs...))
        {
            Delegate<void(TArgs...)> delegate = funcPtr;
            m_delegates.push_back(delegate);
            return delegate;
        }
        
        bool Remove(const Delegate<void(TArgs...)>& delegate)
        {
            auto it = std::find(m_delegates.begin(), m_delegates.end(), delegate);
            if (it != m_delegates.end())
            {
                m_delegates.erase(it);
                return true;
            }
            return false;
        }
        
        void RemoveAll()
        {
            m_delegates.clear();
        }
        
    protected:
        template<typename ...Args>
        void operator()(Args&&... args)
        {
            for (auto delegate : m_delegates)
                delegate(std::forward<Args>(args)...);
        }
        
    private:
        DynamicArray<Delegate<void(TArgs...)>> m_delegates;
    };
}