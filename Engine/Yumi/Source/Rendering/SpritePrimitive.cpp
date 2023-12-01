#include "SpritePrimitive.h"
#include "Sprite.h"

namespace Yumi
{
    SpritePrimitive::SpritePrimitive()  = default;
    SpritePrimitive::~SpritePrimitive() = default;

    void SpritePrimitive::GenerateSpriteVertexData()
    {
        Shape = FragmentShape::Defaut;
        UpdateLocalVertexPositions();
        UpdateVertexPositions();
        UpdateVertexUVs();
        UpdateVertexColors();
    }

    void SpritePrimitive::GenerateCircleVertexData(float radius)
    {
        Shape = FragmentShape::Circle;
        Size = Vector2::One * radius * 2.f;
        UpdateLocalVertexPositions();
        UpdateVertexPositions();
        UpdateVertexUVs();
        UpdateVertexColors();
    }

    void SpritePrimitive::GenerateLineVertexData(const Vector2& start, const Vector2& end, const Vector2& normal)
    {
        Shape = FragmentShape::Defaut;
        UpdateVertexUVs();
        m_VertexPositions[0] = start + normal *  Thickness / 2;
        m_VertexPositions[1] = end   + normal *  Thickness / 2;
        m_VertexPositions[2] = end   + normal * -Thickness / 2;
        m_VertexPositions[3] = start + normal * -Thickness / 2;
        UpdateVertexColors();
    }

    void SpritePrimitive::GenerateRectVertexData()
    {
        Shape = FragmentShape::Rect;
        UpdateVertexUVs();
        UpdateLocalVertexPositions();
        UpdateVertexPositions();
        UpdateVertexColors();
    }
    
    void SpritePrimitive::UpdateLocalVertexPositions()
    {
        m_LocalVertexPositions = SpriteSource ? SpriteSource->GetVertexPositions() : Math::GetDefaultQuadVertexPositions();
    }
    
    void SpritePrimitive::UpdateVertexPositions()
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            m_VertexPositions[i] = Vector4(m_LocalVertexPositions[i], 1.f) * TransformMatrix;
            m_VertexPositions[i].x *= Size.x;
            m_VertexPositions[i].y *= Size.y;
        }
    }
    void SpritePrimitive::UpdateVertexUVs()
    {
        m_VertexUVs = SpriteSource ? SpriteSource->GetVertexUVs() : Math::GetDefaultQuadUVs();

        for (Vector2& vertexUV : m_VertexUVs)
        {
            vertexUV.x *= UVScale.x;
            vertexUV.y *= UVScale.y;
        }

        Math::FlipQuadVertexUVs(FlipMode, m_VertexUVs);
    }

    void SpritePrimitive::UpdateVertexColors()
    {
        for (Color& vertexColor : m_VertexColors)
            vertexColor = TintColor;
    }
}