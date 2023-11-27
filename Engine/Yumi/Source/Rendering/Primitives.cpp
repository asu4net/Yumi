#include "Primitives.h"

namespace Yumi
{
    SpritePrimitive SpritePrimitive::CreateLine(const Vector2& start, const Vector2& end, const Vector2& normal, const Color& color, float thickness)
    {
        SpritePrimitive line;
        for (Color& vertexColor : line.VertexColors) vertexColor = color;
        line.VertexPositions[0] = start + normal *  thickness / 2;
        line.VertexPositions[1] = end   + normal *  thickness / 2;
        line.VertexPositions[2] = end   + normal * -thickness / 2;
        line.VertexPositions[3] = start + normal * -thickness / 2;
        line.VertexUV = Math::GetDefaultSpriteUVs();
        return line;
    }

    SpritePrimitive SpritePrimitive::CreateBox(const Vector3& position, const Vector3& rotation, const Color& color, const Vector2& size, float thickness)
    {
        return SpritePrimitive();
    }

    SpritePrimitive SpritePrimitive::CreateCircle(const Vector3& position, const Vector3& rotation, const Color& color, float radius, float thickness, float fade)
    {
        SpritePrimitive circle;
        
        //apply transform
        circle.VertexPositions = Math::GetDefaultSpriteVertexPositions();
        circle.LocalVertexPositions = Math::GetDefaultSpriteVertexPositions();
        for (Color& vertexColor : circle.VertexColors) vertexColor = color;
        circle.VertexUV = Math::GetDefaultSpriteUVs();
        circle.IsCircle = true;
        circle.Thickness = thickness;
        circle.Fade = fade;
        return circle;
    }
}