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
};

class AnimationScript : public Script
{
    AssetRef AspidAnimationRef;

    void OnStart()
    {
        auto& spriteComponent = Get<SpriteComponent>();
        AspidAnimationRef = GetAssetManager().CreateAnimationAsset(AssetData{ "AspidFly" }, &spriteComponent.SpriteAssetRef);
        Animation::PushKeysFromAtlas("AspidFly", "aspid.png", { 143, 123 }, 6);
        AspidAnimationRef.GetAs<Animation>().Play();
    }

    void OnUpdate()
    {
        auto& aspidAnimation = AspidAnimationRef.GetAs<Animation>();
        aspidAnimation.Update();
    }
};

void CreateActors()
{
    Scene& scene = GetWorld().GetActiveScene();
    
    Actor emptySpriteActor = scene.CreateActor({ "Empty", Vector3::Left });
    emptySpriteActor.Add<SpriteComponent>(Color::LightRed);
    ScriptStatics::Attach<ColorScript>(emptySpriteActor);

    Actor catActor = scene.CreateActor();
    AssetRef catSprite = GetAssetManager().CreateSpriteAsset("Bola.jpg");
    catActor.Add<SpriteComponent>(catSprite);

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    AssetRef cppSprite = GetAssetManager().CreateSpriteAsset("cpp.png");
    cppActor.Add<SpriteComponent>(cppSprite);
    ScriptStatics::Attach<MoveScript>(cppActor);

    Actor aspidActor = scene.CreateActor({ "Aspid", Vector3::Down});
    aspidActor.Add<SpriteComponent>();
    ScriptStatics::Attach<AnimationScript>(aspidActor);
}