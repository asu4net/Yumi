#pragma once
#include "Asset/Asset.h"
#include "Actor.h"

namespace Yumi
{
    class System;

    class Scene : public Asset
    {
    public:
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

        Scene();

        AssetData GetAssetData() const override { return m_AssetData; }
        bool Load() override;
        void Unload() override;

        WeakPtr<entt::registry> GetRegistry() const { return m_Registry; }

        Actor CreateActor(const ActorCreationParams& params = {});

        void SetStartScene(bool isStartScene) { m_IsStartScene = isStartScene; }
        bool IsStartScene() const { return m_IsStartScene; }

        void SetRuntimeEnabled(const bool bRuntimeEnabled) { m_IsRuntimeEnabled = bRuntimeEnabled; }
        bool IsRuntimeEnabled() const { return m_IsRuntimeEnabled; }

        void Start();
        void Update();
        void FixedUpdate();
        void Finish();

    private:
        std::pair<Id, entt::entity> CreateEntity(Id specificId = 0);

        void SetScenePtr(const SharedPtr<Scene> scene) { m_This = scene; }
        void SetAssetData(const AssetData& assetData) override { m_AssetData = assetData; }

        bool m_IsStartScene = false;
        bool m_IsRuntimeEnabled = true;
        DynamicArray<SharedPtr<System>> m_Systems;
        uint32_t m_CreatedActorsCount = 0;
        AssetData m_AssetData;
        SharedPtr<entt::registry> m_Registry;
        Map<Id, entt::entity> m_IdEntityMap;
        SharedPtr<Scene> m_This;

        friend class AssetManager;
    };
}