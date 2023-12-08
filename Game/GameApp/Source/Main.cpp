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

    void OnSubmitGizmos()
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
    catActor.Add<SpriteComponent>("Bola");

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    cppActor.Add<SpriteComponent>("Cpp");
    cppActor.Add<ScriptComponent>(Type::get<MoveScript>());

    Actor aspidActor = scene.CreateActor({"Aspid", Vector3::Down});
    aspidActor.Add<SpriteComponent>("Aspid", SpriteSource::SubSprite);
    aspidActor.Add<AnimationComponent>("AspidFly");

    Actor grid = scene.CreateActor({ "Grid" });
    grid.GetTransform().Scale = Vector3::One * 30.f;
    auto& gridSprite = grid.Add<SpriteComponent>("Checkerboard");
    gridSprite.UVScale = Vector3::One * 30.f;
    gridSprite.TintColor = Color::DarkGray;
}