#include "Script.h"

namespace Yumi
{

    Script::Script() = default;
    Script::~Script() = default;
    
    TransformComponent& Script::GetTransform() const
    {
        return GetActor().GetTransform();
    }

    InformationComponent& Script::GetInformation() const
    {
        return GetActor().GetInformation();
    }

    Scene& Script::GetScene() const
    {
        return *m_Scene;
    }

    void Script::Create()
    {
        OnCreate();
    }

    void Script::Start()
    {
        OnStart();
    }
    
    void Script::Update()
    {
        OnUpdate();
    }

    void Script::FixedUpdate()
    {
        OnFixedUpdate();
    }

    void Script::Finish()
    {
        OnFinish();
    }

    void Script::Destroy()
    {
        OnDestroy();
    }

    void Script::OnCreate()
    {
    }

    void Script::OnStart()
    {
    }

    void Script::OnUpdate()
    {
    }

    void Script::OnFinish()
    {
    }

    void Script::OnFixedUpdate()
    {
    }

    void Script::OnDestroy()
    {
    }
}