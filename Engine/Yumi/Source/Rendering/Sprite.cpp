#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

namespace Yumi
{
    Sprite::Sprite()
    {
        Configuration cfg; // default configuration
        SetConfiguration(cfg);
    }

    Sprite::Sprite(const Configuration& cfg)
    {
        SetConfiguration(cfg);
    }

    Sprite::Sprite(const SharedPtr<Texture2D> texture, const Configuration& cfg /*= {}*/)
        : m_Texture(texture)
    {
        YCHECK(texture, "A valid texture is required!");
        SetConfiguration(cfg);
    }

    Sprite::Sprite(const SharedPtr<SubTexture2D> subTexture, const Configuration& cfg /*= {}*/)
        : m_SubTexture(subTexture)
    {
        YCHECK(subTexture, "A valid SubTexture is required!");
        SetConfiguration(cfg);
    }

    void Sprite::SetTexture(const SharedPtr<Texture2D> texture)
    {
        m_Texture = texture;
        m_SubTexture = nullptr;

        UpdateLocalVertexPositions();
        UpdateVertexPositions(m_Transform);
        UpdateVertexUV();
        FlipVertexUV(m_FlipMode);
    }

    void Sprite::SetTexture(const SharedPtr<SubTexture2D> subTexture)
    {
        m_SubTexture = subTexture;

        if (m_SubTexture)
        {
            const WeakPtr<Texture2D>& parent = subTexture->GetParent();
            YCHECK(parent.expired(), "Missing parent in subtexture");
            m_Texture = parent.lock();
        }
        else
        {
            m_Texture = nullptr;
        }
        
        UpdateLocalVertexPositions();
        UpdateVertexPositions(m_Transform);
        UpdateVertexUV();
        FlipVertexUV(m_FlipMode);
    }

    void Sprite::SetConfiguration(const Configuration& cfg)
    {
        SetSize(cfg.Size);
        SetTransform(cfg.Transform);
        SetTintColor(cfg.TintColor);
        UpdateVertexUV();
        SetFlip(cfg.FlipMode);
        SetUVScale(cfg.UVScale);
    }

    void Sprite::SetTransform(const Matrix4& transform)
    {
        m_Transform = transform;
        UpdateVertexPositions(m_Transform);
    }

    void Sprite::SetTintColor(const Color& color)
    {
        m_TintColor = color;
        
        for (Color& color : m_VertexColors)
            color = m_TintColor;
    }

    void Sprite::SetFlip(Flip flip)
    {
        m_FlipMode = flip;
        FlipVertexUV(flip);
    }

    void Sprite::SetUVScale(const Vector2& scale)
    {
        m_UVScale = scale;

        for (Vector2& uv : m_VertexUVs)
        {
            uv.x *= scale.x;
            uv.y *= scale.y;
        }
    }

    void Sprite::SetSize(const Vector2& size)
    {
        m_Size = size;
        UpdateLocalVertexPositions();
    }

    void Sprite::UpdateVertexUV()
    {
        if (!m_Texture || m_Texture && !m_SubTexture)
        {
            m_VertexUVs = Graphics::GetDefaultSpriteUVs();
        }
        else if (m_Texture && m_SubTexture)
        {
            m_VertexUVs = m_SubTexture->GetVertexUV();
        }
        else
        {
            YCHECK(false, "Unhandled case");
        }        
    }

    void Sprite::UpdateLocalVertexPositions()
    {
        if (m_Texture)
        {
            Graphics::CalculateSpriteVertexPositions(m_SubTexture ? m_SubTexture->GetSize() : m_Texture->GetSize(), m_Size, m_LocalVertexPositions);
        }
        else
        {
            m_LocalVertexPositions = Graphics::GetDefaultSpriteVertexPositions();
        }
    }

    void Sprite::UpdateVertexPositions(const Matrix4& transform)
    {
        for (uint32_t i = 0; i < 4; i++)
        {
            m_VertexPositions[i] = transform * Vector4(m_LocalVertexPositions[i], 1.);
        }
    }

    void Sprite::FlipVertexUV(Flip flip)
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
    }
}