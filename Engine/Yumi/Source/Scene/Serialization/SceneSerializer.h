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
        SceneSerializer(Scene* scene);
        ~SceneSerializer();

        Scene& GetScene() const;

        void Serialize();
        void Deserialize();

    private:
        void SerializeComponent(ComponentType& componentType, const Actor& actor, StringStream& outStream);

        Scene* m_Scene = nullptr;
    };
}