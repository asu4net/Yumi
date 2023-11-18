#include "Yumi.h"

using namespace Yumi;

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

void OnRunCalled()
{
    Scene& scene = GetWorld().GetActiveScene();
    
    Actor emptySpriteActor = scene.CreateActor({ "Empty", Vector3::Left });
    emptySpriteActor.Add<SpriteComponent>(Color::LightRed);

    Actor catActor = scene.CreateActor();
    AssetRef catSprite = GetAssetManager().CreateSpriteAsset("Bola.jpg");
    catActor.Add<SpriteComponent>(catSprite);

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    AssetRef cppSprite = GetAssetManager().CreateSpriteAsset("cpp.png");
    cppActor.Add<SpriteComponent>(cppSprite);

    ScriptStatics::Attach<MoveScript>(cppActor);
}

int main()
{
    CreateEngine();
    GetEngine().OnRun().Add(OnRunCalled);
    GetEngine().Run();
    DestroyEngine();
}