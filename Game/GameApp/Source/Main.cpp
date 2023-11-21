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
    auto& sheetAnimation = aspidActor.Add<SpritesheetAnimationComponent>();

    auto& flyAnimation = SpriteSheetAnimationStatics::PushAnimation(aspidActor, "AspidFly");
    DynamicArray<Vector2> atlasLocations = { {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} };
    SpriteSheetAnimationStatics::PushSpritesheet(flyAnimation, "aspid.png", { 143, 123 }, atlasLocations);
    aspidActor.Add<SpriteComponent>(flyAnimation.Sprites[1]);
}