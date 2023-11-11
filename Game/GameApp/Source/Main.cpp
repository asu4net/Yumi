#include "Yumi.h"

using namespace Yumi;

class MoveScript : public Script
{
    void OnUpdate() override
    {
        GetActor().GetTransform().Position += Vector3::Right * 0.3f * GetDeltaTime();
    }
};

void OnRun()
{
    AssetLink<Scene> currentScene = GetWorld().GetActiveScene();
    currentScene->SetRuntimeEnabled(true);

    Actor catActor = currentScene->CreateActor();
    catActor.Add<SpriteComponent>(GetAssetManager().CreateSpriteFromTexture("Bola.jpg"));
    ScriptStatics::Attach<MoveScript>(catActor);
    
    Actor secondActor = currentScene->CreateActor({ "Cpp", Vector3::Right });
    secondActor.Add<SpriteComponent>(GetAssetManager().CreateSpriteFromTexture("cpp.png"));
}

int main()
{
    CreateEngine();
    GetEngine().OnRun().Add(OnRun);
    GetEngine().Run();
    DestroyEngine();
}