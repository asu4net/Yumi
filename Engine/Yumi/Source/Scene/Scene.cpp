#include "Scene.h"
#include "Components\InformationComponent.h"
#include "Components\TransformComponent.h"
#include "Systems\System.h"
#include "Systems\SpriteSystem.h"
#include "Systems\CameraSystem.h"
#include "Systems\ScriptSystem.h"
#include "Components\CameraComponent.h"
#include "Components\ScriptComponent.h"
#include "Scripting\Scripts\FreeLookCameraScript.h"
#include "Systems\AnimationSystem.h"

namespace Yumi
{
    Scene::Scene()
        : m_Registry(CreateSharedPtr<entt::registry>())
    {
    }

    bool Scene::Load()
    {
        return true;
    }

    void Scene::Unload()
    {
    }

    std::pair<Id, entt::entity> Scene::CreateEntity(const Id specificId)
    {
        const entt::entity entity = m_Registry->create();
        const Id entityId = specificId == Id(0) ? Id() : specificId;
        m_IdEntityMap[entityId] = entity;
        return { entityId, entity };
    }

    void Scene::CreateFreeLookCamera()
    {
        ActorCreationParams creationParams;
        creationParams.Name = "Free Look Camera Actor";
        creationParams.IsSerializable = false;
        m_FreeLookCameraActor = CreateActor(creationParams);
        m_FreeLookCameraActor.Add<CameraComponent>();
        ScriptComponent& scriptComponent = m_FreeLookCameraActor.Add<ScriptComponent>();
        scriptComponent.ExecutionContext = ScriptExecutionContext::Always;
        ScriptStatics::Attach<FreeLookCameraScript>(m_FreeLookCameraActor);
        SetMainCameraActor(m_FreeLookCameraActor);
    }

    Actor Scene::CreateActor(const ActorCreationParams& params)
    {
        const auto& [id, entity] = CreateEntity(params.SpecificId);
        const String Name = params.Name.empty() ? String().append("Actor [" + std::to_string(m_CreatedActorsCount) + "]") : params.Name;
        m_Registry->emplace<InformationComponent>(entity, params.Name, id, params.IsSerializable);
        m_Registry->emplace<TransformComponent>(entity, params.Position, params.Rotation, params.Scale);
        const Actor actor(entity, m_Registry);
        m_CreatedActorsCount++;
        return actor;
    }

    void Scene::SetMainCameraActor(Actor actor)
    {
        YCHECK(!m_CameraSystem.expired(), "Not a valid camera system");
        m_CameraSystem.lock()->SetMainCameraActor(actor);
    }

    Actor Scene::GetMainCameraActor() const
    {
        YCHECK(m_CameraSystem.expired(), "Not a valid camera system");
        return m_CameraSystem.lock()->GetMainCameraActor();
    }

    void Scene::Prepare()
    {
        m_Systems.push_back(CreateSharedPtr<ScriptSystem>(m_This));
        m_Systems.push_back(CreateSharedPtr<AnimationSystem>(m_This));
        m_Systems.push_back(CreateSharedPtr<CameraSystem>(m_This));
        m_Systems.push_back(CreateSharedPtr<SpriteSystem>(m_This));

        m_CameraSystem = GetSystemOfType<CameraSystem>();
        CreateFreeLookCamera();
    }
    
    void Scene::Start()
    {
        for (SharedPtr<System> system : m_Systems)
            system->OnStart();
        m_IsStarted = true;
    }

    void Scene::Update()
    {
        for (SharedPtr<System> system : m_Systems)
            system->OnUpdate();
    }

    void Scene::FixedUpdate()
    {
        for (SharedPtr<System> system : m_Systems)
            system->OnFixedUpdate();
    }

    void Scene::Finish()
    {
        for (SharedPtr<System> system : m_Systems)
            system->OnFinish();
        m_IsStarted = false;
    }
}