#pragma once

#define YUMI_SINGLETON(_CLASS_NAME) \
    private: \
        _CLASS_NAME(_CLASS_NAME&&) = delete; \
        friend class Yumi::Singleton<_CLASS_NAME>;

namespace Yumi
{
    template<typename T>
    class Singleton
    {
    public:
        static bool HasInstance() { return m_Instance; }

        static T& GetInstance()
        {
            assert(HasInstance() && "There is no instance to retrieve!");
            return *m_Instance;
        }

        static T& CreateInstance()
        {
            assert(!m_Instance && "Instance already exists!");
            m_Instance = new T();
            return GetInstance();
        }

        static void DestroyInstance()
        {
            assert(m_Instance && "There is no instance to destroy!");
            delete m_Instance;
        }

    private:
        inline static T* m_Instance = nullptr;
    };
}
