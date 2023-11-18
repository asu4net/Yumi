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
    
    Actor spriteActor = scene.CreateActor();
    spriteActor.Add<SpriteComponent>(GetAssetManager().CreateSpriteAsset("Bola.jpg"));

    Actor cppActor = scene.CreateActor({"Cpp", Vector3::Right});
    cppActor.Add<SpriteComponent>(GetAssetManager().CreateSpriteAsset("cpp.png"));
    ScriptStatics::Attach<MoveScript>(cppActor);
}

int main()
{
    CreateEngine();
    GetEngine().OnRun().Add(OnRunCalled);
    GetEngine().Run();
    DestroyEngine();
}