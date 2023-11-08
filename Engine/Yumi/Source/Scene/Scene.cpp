#include "Scene.h"
#include "Components\InformationComponent.h"
#include "Components\TransformComponent.h"
#include "Systems\System.h"
#include "Systems\SpriteSystem.h"

namespace Yumi
{
    Scene::Scene()
        : m_Registry(CreateSharedPtr<entt::registry>())
    {
        m_Systems.push_back(CreateSharedPtr<SpriteSystem>(this));
        m_Systems[0]->OnCreate();
    }

    bool Scene::Load()
    {
        // TODO: Implement scene serialization
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

    void Scene::Start()
    {
        for (SharedPtr<System> system : m_Systems)
            system->OnStart();
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
    }
}