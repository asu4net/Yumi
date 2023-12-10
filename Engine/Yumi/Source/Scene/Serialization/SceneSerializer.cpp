#include "SceneSerializer.h"
#include "Scene\Scene.h"
#include "Scene\Actor.h"
#include "Scene\Components\InformationComponent.h"
#include "Scene\Components\TransformComponent.h"
#include "Asset\AssetRef.h"
#include "..\Components\SpriteComponent.h"

RTTR_REGISTRATION
{
    using namespace Yumi;
    rttr::registration::class_<ComponentInfo>("ComponentInfo")
        .constructor<>()
        .property("ComponentType", &ComponentInfo::ComponentType);
}

namespace Yumi
{
    SceneSerializer::SceneSerializer() = default;

    SceneSerializer::SceneSerializer(Scene* scene)
        : m_Scene(scene)
    {
    }

    SceneSerializer::~SceneSerializer() = default;

    Scene& SceneSerializer::GetScene() const
    {
        return *m_Scene;
    }

    void SceneSerializer::Serialize()
    {
        Scene& scene = GetScene();
        WeakPtr<entt::registry> registryPtr = scene.GetRegistry();
        YCHECK(!registryPtr.expired(), "The scene needs a valid registry!");
        entt::registry& sceneRegistry = *registryPtr.lock();

        StringStream jsonSceneStream;

        entt::runtime_view entityView{};
        entityView.iterate(sceneRegistry.storage<entt::entity>());

        entityView.each([&](const entt::entity entity) {

            const Actor actor = { entity, registryPtr };

            if (!actor.Has<InformationComponent>() ||
                !actor.Has<TransformComponent>() ||
                !actor.Get<InformationComponent>().IsSerializable)
                return;

            jsonSceneStream << "#actor start" << std::endl;

            ComponentType& informationCmpType = *ComponentReflection::GetComponentOfType(Type::get<InformationComponent>());
            SerializeComponent(informationCmpType, actor, jsonSceneStream);

            ComponentType& transformCmpType = *ComponentReflection::GetComponentOfType(Type::get<TransformComponent>());
            SerializeComponent(transformCmpType, actor, jsonSceneStream);

            ComponentReflection::Each({[&](Type classType, SharedPtr<ComponentType> componentType) {
                
                if (classType == informationCmpType.GetType() || classType == transformCmpType.GetType())
                    return;
                SerializeComponent(*componentType, actor, jsonSceneStream);
            }});

            jsonSceneStream << "#actor end" << std::endl;
        });

        scene.m_Data = jsonSceneStream.str();
    }

    void SceneSerializer::Deserialize()
    {
        Scene& scene = GetScene();

        WeakPtr<entt::registry> registryPtr = scene.GetRegistry();
        YCHECK(!registryPtr.expired(), "The scene needs a valid registry!");
        entt::registry& sceneRegistry = *registryPtr.lock();

        IStringStream jsonSceneStream{ scene.GetData() };

        Actor actor;
        String componentInfoStr;
        String componentDataStr;
        ComponentInfo componentInfo;

        enum class ReadMode
        {
            None,
            ActorStart,
            ActorEnd,
            ComponentInfoStart,
            ComponentInfoEnd,
            ComponentDataStart,
            ComponentDataEnd
        };

        ReadMode readMode = ReadMode::None;

        for (String line; std::getline(jsonSceneStream, line); )
        {
            if (line.find("#actor start") != String::npos)
            {
                readMode = ReadMode::ActorStart;
            }

            if (line.find("#actor end") != String::npos)
            {
                readMode = ReadMode::ActorEnd;
            }

            if (line.find("#component info start") != String::npos)
            {
                readMode = ReadMode::ComponentInfoStart;
                continue;
            }

            if (line.find("#component info end") != String::npos)
            {
                readMode = ReadMode::ComponentInfoEnd;
            }

            if (line.find("#component data start") != String::npos)
            {
                readMode = ReadMode::ComponentDataStart;
                continue;
            }

            if (line.find("#component data end") != String::npos)
            {
                readMode = ReadMode::ComponentDataEnd;
            }

            // Serialization

            switch (readMode)
            {
            case ReadMode::ActorStart:
            {
                actor = { sceneRegistry.create(), registryPtr };
            }
            continue;
            case ReadMode::ComponentInfoStart:
            {
                componentInfoStr.append(line + "\n");
            }
            continue;
            case ReadMode::ComponentInfoEnd:
            {
                Serialization::FromJson(componentInfoStr, componentInfo);
                componentInfoStr.clear();
            }
            continue;
            case ReadMode::ComponentDataStart:
            {
                componentDataStr.append(line + "\n");
            }
            continue;
            case ReadMode::ComponentDataEnd:
            {
                Type componentClassType = Type::get_by_name(componentInfo.ComponentType);
                if (!componentClassType.is_valid())
                    continue;

                Variant variant = componentClassType.create();
                if (!variant.is_valid())
                    continue;

                Instance componentInstance = variant;
                if (!componentInstance.is_valid())
                    continue;

                Serialization::FromJson(componentDataStr, componentInstance);

                auto componentType = ComponentReflection::GetComponentOfType(componentClassType);

                componentType->AddComponent(actor, componentInstance);
                
                componentDataStr.clear();
            }
            continue;
            case ReadMode::ActorEnd:
                scene.m_IdEntityMap[actor.Get<InformationComponent>().ID] = actor.GetEntity();
                continue;
            }
        }
    }

    void SceneSerializer::SerializeComponent(ComponentType& componentType, const Actor& actor, StringStream& outStream)
    {
        if (!componentType.HasComponent(actor))
        {
            return;
        }

        const ComponentInfo componentInfo { componentType.GetType().get_name().to_string() };
        const Instance componentData = componentType.GetComponentByCopy(actor);

        outStream << "#component info start" << std::endl;
        outStream << Serialization::ToJson(componentInfo) << std::endl;
        outStream << "#component info end" << std::endl;
        
        outStream << "#component data start" << std::endl;
        outStream << Serialization::ToJson(componentData) << std::endl;
        outStream << "#component data end" << std::endl;
    }
}