#pragma once

namespace Yumi
{
    enum class FragmentShape : uint32_t
    {
        Defaut   = 0,
        Circle = 1,
        Rect   = 2
    };
    
    class Sprite;

    class SpritePrimitive
    {
    public:
        SpritePrimitive();
        ~SpritePrimitive();

        const Array<Vector3, 4>& GetLocalVertexPositions() const { return m_LocalVertexPositions; }
        const Array<Vector3, 4>& GetVertexPositions()      const { return m_VertexPositions; }
        const Array<Vector2, 4>& GetVertexUV()             const { return m_VertexUVs; }
        const Array<Color, 4>&   GetVertexColors()         const { return m_VertexColors; }
        
        void GenerateSpriteVertexData();
        void GenerateCircleVertexData(float radius);
        void GenerateLineVertexData(const Vector2& start, const Vector2& end, const Vector2& normal);
        void GenerateRectVertexData();

        // Used to generate vertex data
        Matrix4           TransformMatrix;
        Vector2           Size = Vector2::One;
        Color             TintColor = Color::White;
        Flip              FlipMode = Flip::None;
        Vector2           UVScale = Vector2::One;

        // Vertex data
        SharedPtr<Sprite> SpriteSource = nullptr;
        FragmentShape     Shape = FragmentShape::Defaut;
        float             Thickness = .05f;
        float             Fade = .01f;
        Vector2           Bounds = Vector2::Zero;

    private:
        void UpdateLocalVertexPositions();
        void UpdateVertexPositions();
        void UpdateVertexUVs();
        void UpdateVertexColors();

        // Vertex data
        Array<Vector3, 4> m_LocalVertexPositions;
        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUVs;
        Array<Color, 4>   m_VertexColors;
    };
}