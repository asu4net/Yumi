#pragma once
#include "Scene\Scene.h"

namespace Yumi
{
    class Scene;
    struct TransformComponent;
    struct InformationComponent;

    class Script
    {
    public:
        Script();
        virtual ~Script();
        
        Actor GetActor() const { return m_Actor; }
        TransformComponent& GetTransform() const;
        InformationComponent& GetInformation() const;
        Scene& GetScene() const;

        template<typename T>
        bool Has() const
        {
            return m_Actor.Has<T>();
        }

        template<typename T, typename... TArgs>
        T& Add(TArgs&&... args) const
        {
            return m_Actor.Add<T>(std::forward<TArgs>(args)...);
        }

        template<typename T>
        T& Get() const
        {
            return m_Actor.Get<T>();
        }

        template<typename T>
        void Remove() const
        {
            m_Actor.Remove<T>();
        }

        void Create();
        void Start();
        void Update();
        void FixedUpdate();
        void Finish();
        void Destroy();

    protected:
        virtual void OnCreate();
        virtual void OnStart();
        virtual void OnUpdate();
        virtual void OnFinish();
        virtual void OnFixedUpdate();
        virtual void OnDestroy();

    private:
        Actor m_Actor;
        SharedPtr<Scene> m_Scene;

        friend class ScriptSystem;
        friend struct ScriptStatics;
    };
}