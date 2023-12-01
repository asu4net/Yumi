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
        rectSprite.TintColor = Color::Cyan;
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
};

void CreateActors()
{
    AssetRef catSpriteRef = GetAssetManager().CreateAsset<Sprite>("Bola.jpg [Sprite]", "Bola.jpg");
    AssetRef cppSpriteRef = GetAssetManager().CreateAsset<Sprite>("cpp.png [Sprite]", "cpp.png");
    AssetRef aspidAnimationRef = GetAssetManager().CreateAsset<Animation>("AspidFly");

    Scene& scene = GetWorld().GetActiveScene();
    
    Actor emptySpriteActor = scene.CreateActor({ "Empty", Vector3::Left });
    emptySpriteActor.Add<SpriteComponent>(Color::LightRed);
    ScriptStatics::Attach<ColorScript>(emptySpriteActor);

    Actor catActor = scene.CreateActor();
    catActor.Add<SpriteComponent>(catSpriteRef);

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    cppActor.Add<SpriteComponent>(cppSpriteRef);
    ScriptStatics::Attach<MoveScript>(cppActor);

    Actor aspidActor = scene.CreateActor({ "Aspid", Vector3::Down});
    auto& spriteComponent = aspidActor.Add<SpriteComponent>();
    Animation::PushKeysFromAtlas("AspidFly", "aspid.png", { 143, 123 }, 6);
    aspidActor.Add<AnimationComponent>(aspidAnimationRef, &spriteComponent.SpriteAssetRef);
}