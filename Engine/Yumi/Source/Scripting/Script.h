#pragma once
#include "Scene\Scene.h"

namespace Yumi
{
    class Scene;
    struct TransformComponent;
    struct InformationComponent;

#define YSCRIPT_EXECUTION_CONTEXT(_CONTEXT) \
    ExecutionContext GetExecutionContext() const override { return ExecutionContext::_CONTEXT; }

#define YSCRIPT_EXECUTION_ORDER(_ORDER) \
    int GetExecutionOrder() const override { return _ORDER; }

    class Script
    {
    public:
        enum class ExecutionContext
        {
            Game,
            Editor,
            Both
        };

        Script();
        virtual ~Script();

        virtual ExecutionContext GetExecutionContext() const { return ExecutionContext::Game; }
        virtual int GetExecutionOrder() const { return 0; }

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
        bool m_Started = false;

        friend class ScriptSystem;
        friend struct ScriptStatics;
    };
}