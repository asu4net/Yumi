#include "Yumi.h"

using namespace Yumi;

int main()
{
    CreateEngine();
    InitEngine();
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