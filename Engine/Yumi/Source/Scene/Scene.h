#pragma once
#include "Asset/Asset.h"
#include "Actor.h"

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
        bool IsSerializable;
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

        AssetData GetAssetData() const override { return m_AssetData; }
        void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; }
        bool Load() override;
        void Unload() override;

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
        void Finish();

    private:
        std::pair<Id, entt::entity> CreateEntity(Id specificId = 0);
        void CreateFreeLookCamera();

        WeakPtr<class CameraSystem> m_CameraSystem;
        Actor m_FreeLookCameraActor;
        bool m_IsStartScene = false;
        bool m_IsRuntimeEnabled = true;
        bool m_IsStarted = false;
        DynamicArray<SharedPtr<System>> m_Systems;
        uint32_t m_CreatedActorsCount = 0;
        AssetData m_AssetData;
        SharedPtr<entt::registry> m_Registry;
        Map<Id, entt::entity> m_IdEntityMap;
        SharedPtr<Scene> m_This;

        friend class AssetManager;
    };
}