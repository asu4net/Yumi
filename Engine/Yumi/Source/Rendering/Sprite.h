#pragma once

namespace Yumi
{
    class Texture2D;
    class SubTexture2D;

    class Sprite
    {
    public:
        struct Configuration
        {
            Matrix4 Transform;
            Color TintColor = Color::White;
            Vector2 Size = Vector2::One;
            Flip FlipMode = Flip::None;
            Vector2 UVScale = Vector2::One;
        };

        Sprite();
        Sprite(const Configuration& cfg);
        Sprite(const SharedPtr<Texture2D> texture, const Configuration& cfg = {});
        Sprite(const SharedPtr<SubTexture2D> subTexture, const Configuration& cfg = {});
        
        void SetTexture(const SharedPtr<Texture2D> texture);
        SharedPtr<Texture2D> GetTexture() const { return m_Texture; }

        void SetTexture(const SharedPtr<SubTexture2D> subTexture);
        SharedPtr<SubTexture2D> GetSubTexture() const { return m_SubTexture; }
        
        void SetConfiguration(const Configuration& cfg);

        void SetTransform(const Matrix4& transform);
        Matrix4 GetTransform() const { return m_Transform; }

        void SetTintColor(const Color& color);
        Color GetTintColor() const { return m_TintColor; }

        void SetSize(const Vector2& size);
        Vector2 GetSize() const { return m_Size; }

        void SetFlip(Flip flip);
        Flip GetFlip() const { return m_FlipMode; }

        void SetUVScale(const Vector2& scale);
        Vector2 GetUVScale() const { return m_UVScale; }

        const Array<Vector3, 4>& GetVertexPositions() const { return m_VertexPositions; }
        const Array<Vector2, 4>& GetVertexUVs() const { return m_VertexUVs; }
        const Array<Color, 4>& GetVertexColors() const { return m_VertexColors; }

    private:
        void UpdateVertexUV();
        void UpdateLocalVertexPositions();
        void UpdateVertexPositions(const Matrix4& transform);
        void FlipVertexUV(Flip flip);

        SharedPtr<Texture2D> m_Texture;
        SharedPtr<SubTexture2D> m_SubTexture;
        Matrix4 m_Transform;
        Color m_TintColor;
        Vector2 m_Size;
        Flip m_FlipMode = Flip::None;
        Vector2 m_UVScale;
        Array<Vector3, 4> m_LocalVertexPositions;
        
        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUVs;
        Array<Color, 4> m_VertexColors;
    };
}