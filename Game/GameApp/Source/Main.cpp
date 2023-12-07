#include "Yumi.h"

using namespace Yumi;

void CreateActors();

int main()
{
    CreateEngine();
    InitEngine();
    CreateActors();
    RunEngine();
    DestroyEngine();
}

class MoveScript : public Script
{
    float speed = 5.f;

    void OnUpdate()
    {
        if (GetInput().IsKeyPressed(KEY_D))
            GetTransform().Position += Vector3::Right * speed * GetDeltaTime();
        if (GetInput().IsKeyPressed(KEY_A))
            GetTransform().Position += Vector3::Left * speed * GetDeltaTime();
    }

    RTTR_ENABLE(Script)
};

class ColorScript : public Script
{
    bool SpacePressed = false;

    void OnUpdate()
    {
        SpritePrimitive lineSprite;
        lineSprite.TintColor = Color::Yellow;
        lineSprite.GenerateVertexData(SpriteShape::Line);
        GetRenderer().SubmitSpritePrimitive(lineSprite);

        SpritePrimitive circleSprite;
        circleSprite.TintColor = Color::Green;
        circleSprite.GenerateVertexData(SpriteShape::Circle);
        GetRenderer().SubmitSpritePrimitive(circleSprite);

        SpritePrimitive rectSprite;
        rectSprite.TransformMatrix = Matrix4::CreateTransform(Vector3::Down + Vector3::Right);
        rectSprite.TintColor = Color::Clear;
        rectSprite.GenerateVertexData(SpriteShape::Rect);
        GetRenderer().SubmitSpritePrimitive(rectSprite);

        SpriteComponent& spriteComponent = Get<SpriteComponent>();

        if (!SpacePressed && GetInput().IsKeyPressed(KEY_SPACE))
        {
            static bool bSwitch = false;
            spriteComponent.TintColor = bSwitch ? Color::Blue : Color::Yellow;
            bSwitch = !bSwitch;
            SpacePressed = true;
        }
        else if (!GetInput().IsKeyPressed(KEY_SPACE))
        {
            SpacePressed = false;
        }
    }

    RTTR_ENABLE(Script)
};

namespace main_registration
{
    RTTR_REGISTRATION
    {
        rttr::registration::class_<MoveScript>("MoveScript").constructor<>();
        rttr::registration::class_<ColorScript>("ColorScript").constructor<>();
    }
}

void CreateActors()
{
    Scene& scene = GetWorld().GetActiveScene();
    
    Actor emptySpriteActor = scene.CreateActor({ "Empty", Vector3::Left });
    emptySpriteActor.Add<SpriteComponent>(Color::LightRed);
    emptySpriteActor.Add<ScriptComponent>(Type::get<ColorScript>());

    Actor catActor = scene.CreateActor();
    catActor.Add<SpriteComponent>("Bola [Sprite]");

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    cppActor.Add<SpriteComponent>("Cpp [Sprite]");
    cppActor.Add<ScriptComponent>(Type::get<MoveScript>());

    Actor aspidActor = scene.CreateActor({ "Aspid", Vector3::Down});
    auto& spriteComponent = aspidActor.Add<SpriteComponent>();
    Animation::PushKeysFromAtlas("AspidFly [Animation]", "Aspid [Texture]", { 143, 123 }, 6);
    aspidActor.Add<AnimationComponent>(GetAssetManager().GetAssetByName("AspidFly [Animation]"), &spriteComponent.SpriteAssetRef);
}