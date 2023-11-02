#pragma once

namespace Yumi
{
    class Texture2D;
    class SubTexture2D;

    class Sprite
    {
    public:
        struct Settings
        {
            Matrix4 Transform;
            Color TintColor = Color::White;
            Vector2 Size = Vector2::One;
            Flip FlipMode = Flip::None;
            Vector2 UVScale = Vector2::One;
        };

        Sprite();
        Sprite(const Settings& settings);
        Sprite(const SharedPtr<Texture2D> texture, const Settings& settings = {});
        Sprite(const SharedPtr<SubTexture2D> subTexture, const Settings& settings = {});
        
        void SetTexture(const SharedPtr<Texture2D> texture);
        SharedPtr<Texture2D> GetTexture() const { return m_Texture; }

        void SetSubTexture(const SharedPtr<SubTexture2D> subTexture);
        SharedPtr<SubTexture2D> GetSubTexture() const { return m_SubTexture; }

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
        const Array<Vector2, 4>& GetVertexUV() const { m_VertexUV; }

    private:
        void InitSettings(const Settings& settings);
        void SetVertexUV(const Array<Vector2, 4>& uv);
        void ReCalculateVertexPositions(const Vector2& textureSize);
        void ApplyTransformToVertexPositions();

        SharedPtr<Texture2D> m_Texture;
        SharedPtr<SubTexture2D> m_SubTexture;
        Matrix4 m_Transform;
        Color m_TintColor;
        Vector2 m_Size;
        Flip m_FlipMode = Flip::None;
        Vector2 m_UVScale;
        Array<Vector3, 4> m_VertexPositions;
        Array<Vector2, 4> m_VertexUV;
        Array<Color, 4> m_VertexColors;
    };
}