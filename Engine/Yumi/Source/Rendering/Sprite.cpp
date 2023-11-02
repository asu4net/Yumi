#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

namespace Yumi
{
    static const Array<Vector2, 4>& DefaultSpriteUV()
    {
        static Array<Vector2, 4> uv = 
        {
            Vector2(0, 0), // bottom-left
            Vector2(1, 0), // bottom-right
            Vector2(1, 1), // top-right
            Vector2(0, 1), // top-left
        };
        return uv;
    }

    static const Array<Vector3, 4>& DefaultSpriteVertexPositions()
    {
        static Array<Vector3, 4> vertexPositions =
        {
            Vector3(-.5f, -.5f, 0),
            Vector3( .5f, -.5f, 0),
            Vector3( .5f,  .5f, 0),
            Vector3(-.5f,  .5f, 0)
        };
        return vertexPositions;
    }

    static void CalculateSpriteVertexPositions(const Vector2& textureSize, const Vector2& spriteSize, Array<Vector3, 4>& vertexPositions)
    {
        static Vector2 s_VertexMag = Vector2::One / 2;
        Vector2 pos = s_VertexMag;

        if (std::abs(textureSize.x - textureSize.y) > 0.0001f)
            pos = textureSize.Normalized() / 2;

        pos.x *= spriteSize.x;
        pos.y *= spriteSize.y;

        vertexPositions[0] = { -pos.x, -pos.y, 0 };
        vertexPositions[1] = {  pos.x, -pos.y, 0 };
        vertexPositions[2] = {  pos.x,  pos.y, 0 };
        vertexPositions[3] = { -pos.x,  pos.y, 0 };
    }

    Sprite::Sprite()
    {
        m_VertexLayout = DefaultSpriteVertexPositions();
        m_VertexPositions = m_VertexLayout;

        Settings settings;
        SetTransform(settings.Transform);
        SetVertexUV(DefaultSpriteUV());
        SetTintColor(settings.TintColor);
        SetUVScale(settings.UVScale);
        SetFlip(settings.FlipMode);
        SetSize(settings.Size);
    }

    Sprite::Sprite(const Settings& settings)
    {
        SetSize(settings.Size);
        SetTransform(settings.Transform);
        SetVertexUV(DefaultSpriteUV());
        SetTintColor(settings.TintColor);
        SetUVScale(settings.UVScale);
        SetFlip(settings.FlipMode);
        SetSize(settings.Size);
    }

    Sprite::Sprite(const SharedPtr<Texture2D> texture, const Settings& settings /*= {}*/)
        : m_Texture(texture)
    {
        YCHECK(texture, "A valid texture is required!");
        SetSize(settings.Size);
        SetTransform(settings.Transform);
        SetVertexUV(DefaultSpriteUV());
        SetTintColor(settings.TintColor);
        SetUVScale(settings.UVScale);
        SetFlip(settings.FlipMode);
        SetSize(settings.Size);
    }

    Sprite::Sprite(const SharedPtr<SubTexture2D> subTexture, const Settings& settings /*= {}*/)
        : m_SubTexture(subTexture)
    {
        YCHECK(subTexture, "A valid SubTexture is required!");
        SetSize(settings.Size);
        SetTransform(settings.Transform);
        SetVertexUV(subTexture->GetVertexUV());
        SetTintColor(settings.TintColor);
        SetUVScale(settings.UVScale);
        SetFlip(settings.FlipMode);
    }

    void Sprite::SetTexture(const SharedPtr<Texture2D> texture)
    {
        if (m_SubTexture)
            m_SubTexture = nullptr;
        
        m_Texture = texture;

        if (m_Texture)
        {
            CalculateSpriteVertexPositions(texture->GetSize(), m_Size, m_VertexLayout);
        }
        else
        {
            m_VertexPositions = DefaultSpriteVertexPositions();
        }

        SetVertexUV(DefaultSpriteUV());
    }

    void Sprite::SetSubTexture(const SharedPtr<SubTexture2D> subTexture)
    {
        YCHECK(subTexture, "Missing subtexture!");

        const WeakPtr<Texture2D>& parent = subTexture->GetParent();
        YCHECK(parent.expired(), "Missing parent in subtexture");

        m_Texture = parent.lock();
        m_SubTexture = subTexture;

        CalculateSpriteVertexPositions(subTexture->GetSize(), m_Size, m_VertexLayout);
        m_VertexPositions = m_VertexLayout;

        SetVertexUV(m_SubTexture->GetVertexUV());
    }

    void Sprite::SetTransform(const Matrix4& transform)
    {
        m_Transform = transform;

        for (uint32_t i = 0; i < 4; i++)
        {
            m_VertexPositions[i] = m_Transform * Vector4(m_VertexLayout[i], 1.);
        }
    }

    void Sprite::SetTintColor(const Color& color)
    {
        m_TintColor = color;
        
        for (Color& color : m_VertexColors)
            color = m_TintColor;
    }

    void Sprite::SetVertexUV(const Array<Vector2, 4>& uv)
    {
        m_VertexUVs = uv;
        SetFlip(m_FlipMode);
    }

    void Sprite::SetFlip(Flip flip)
    {
        Array<Vector2, 4> uv = m_VertexUVs;

        switch (flip)
        {
        case Flip::None:
            m_VertexUVs = uv;
            return;
        case Flip::X:
            m_VertexUVs[0] = uv[1];
            m_VertexUVs[1] = uv[0];
            m_VertexUVs[2] = uv[3];
            m_VertexUVs[3] = uv[2];
            return;
        case Flip::Y:
            m_VertexUVs[0] = uv[2];
            m_VertexUVs[1] = uv[3];
            m_VertexUVs[2] = uv[0];
            m_VertexUVs[3] = uv[1];
            return;
        case Flip::Both:
            m_VertexUVs[0] = uv[3];
            m_VertexUVs[1] = uv[2];
            m_VertexUVs[2] = uv[1];
            m_VertexUVs[3] = uv[0];
        }

        m_FlipMode = flip;
    }

    void Sprite::SetUVScale(const Vector2& scale)
    {
        m_UVScale = scale;

        for (Vector2& uvScale : m_VertexUVScales)
            uvScale = m_UVScale;
    }

    void Sprite::SetSize(const Vector2& size)
    {
        m_Size = size;
        
        if (m_Texture)
        {
            CalculateSpriteVertexPositions(m_SubTexture ? m_SubTexture->GetSize() : m_Texture->GetSize(),
                m_Size, m_VertexLayout);
            m_VertexPositions = m_VertexLayout;
        }
        else
        {
            m_VertexLayout = DefaultSpriteVertexPositions();
        }
    }
}