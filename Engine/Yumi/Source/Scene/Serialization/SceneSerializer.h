#pragma once

namespace Yumi
{
    class Scene;
    class Actor;

    struct ComponentInfo
    {
        String ComponentType;
        RTTR_ENABLE_NO_VIRTUAL
    };

    class SceneSerializer
    {
    public:
        SceneSerializer();
        SceneSerializer(const WeakPtr<Scene>& scene);
        ~SceneSerializer();

        Scene& GetScene() const;

        void Serialize();
        void Deserialize();

    private:
        void SerializeComponent(ComponentType& componentType, const Actor& actor, StringStream& outStream);

        WeakPtr<Scene> m_Scene;
    };
}