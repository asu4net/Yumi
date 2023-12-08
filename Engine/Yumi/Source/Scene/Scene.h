#pragma once
#include "Asset/Asset.h"
#include "Actor.h"
#include "Serialization/SceneSerializer.h"

namespace Yumi
{
    class System;

    struct ActorCreationParams
    {
        String Name;
        Vector3 Position;
        Vector3 Rotation;
        Vector3 Scale = Vector3::One;
        Id SpecificId = 0;
        bool IsSerializable = true;
        // TODO: component type collection
    };

    class Scene : public Asset
    {
    public:
        Scene();

        template<typename T>
        WeakPtr<T> GetSystemOfType()
        {
            SharedPtr<T> resultSystem;

            for (SharedPtr<System> system : m_Systems)
            {
                resultSystem = std::dynamic_pointer_cast<T>(system);
                if (resultSystem) break;
            }

            YCHECK(resultSystem, "There is no system of the given type");
            return resultSystem;
        }

        bool Load() override;
        void Unload() override;

        String GetData() const { return m_Data; }

        void SetScenePtr(const SharedPtr<Scene> scene) { m_This = scene; }

        WeakPtr<entt::registry> GetRegistry() const { return m_Registry; }

        Actor CreateActor(const ActorCreationParams& params = {});

        void SetMainCameraActor(Actor actor);
        Actor GetMainCameraActor() const;

        void SetStartScene(bool isStartScene) { m_IsStartScene = isStartScene; }
        bool IsStartScene() const { return m_IsStartScene; }

        void SetRuntimeEnabled(const bool bRuntimeEnabled) { m_IsRuntimeEnabled = bRuntimeEnabled; }
        bool IsRuntimeEnabled() const { return m_IsRuntimeEnabled; }

        bool IsStarted() const { return m_IsStarted; }

        void Prepare();
        void Start();
        void Update();
        void FixedUpdate();
        void SubmitGizmos();
        void Finish();

    private:
        std::pair<Id, entt::entity> CreateEntity(Id specificId = 0);
        void CreateFreeLookCamera();

        String m_Data;
        SceneSerializer m_Serializer;
        WeakPtr<class CameraSystem> m_CameraSystem;
        Actor m_FreeLookCameraActor;
        bool m_IsStartScene = false;
        bool m_IsRuntimeEnabled = true;
        bool m_IsStarted = false;
        DynamicArray<SharedPtr<System>> m_Systems;
        uint32_t m_CreatedActorsCount = 0;
        SharedPtr<entt::registry> m_Registry;
        Map<Id, entt::entity> m_IdEntityMap;
        SharedPtr<Scene> m_This;

        RTTR_ENABLE(Asset)
        friend class SceneSerializer;
    };

    YFORCE_LINK(Scene)
    YDECLARE_ASSET_EXTENSION(Scene, yumi)
}