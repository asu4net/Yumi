#include "Sprite.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

namespace Yumi
{
    static const Array<Vector2, 4>& DefaultSpriteUV()
    {
        static Array<Vector2, 4> uv = 
        {
            Vector2( -1, -1 ),
            Vector2(  1, -1 ),
            Vector2(  1,  1 ),
            Vector2( -1,  1 )
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

    Sprite::Sprite()
    {
        InitSettings({});
        m_VertexPositions = DefaultSpriteVertexPositions();
        SetVertexUV(DefaultSpriteUV());
    }

    Sprite::Sprite(const Settings& settings)
    {
        InitSettings(settings);
        m_VertexPositions = DefaultSpriteVertexPositions();
        ApplyTransformToVertexPositions();
        SetVertexUV(DefaultSpriteUV());
    }

    Sprite::Sprite(const SharedPtr<Texture2D> texture, const Settings& settings /*= {}*/)
        : m_Texture(texture)
    {
        InitSettings(settings);
        m_VertexPositions = DefaultSpriteVertexPositions();
        ApplyTransformToVertexPositions();
        SetVertexUV(DefaultSpriteUV());
    }

    Sprite::Sprite(const SharedPtr<SubTexture2D> subTexture, const Settings& settings /*= {}*/)
        : m_SubTexture(subTexture)
    {
        InitSettings(settings);
        ReCalculateVertexPositions(subTexture->GetSize());
        ApplyTransformToVertexPositions();
        SetVertexUV(subTexture->GetVertexUV());
    }

    void Sprite::SetTexture(const SharedPtr<Texture2D> texture)
    {
        if (m_SubTexture)
            m_SubTexture = nullptr;
        
        m_Texture = texture;

        if (m_Texture)
        {
            ReCalculateVertexPositions(m_Texture->GetSize());
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

        ReCalculateVertexPositions(m_SubTexture->GetSize());
        SetVertexUV(m_SubTexture->GetVertexUV());
    }

    void Sprite::SetTransform(const Matrix4& transform)
    {
        m_Transform = transform;
        ApplyTransformToVertexPositions();
    }

    void Sprite::SetTintColor(const Color& color)
    {
        m_TintColor = color;
    }

    void Sprite::InitSettings(const Settings& settings)
    {
        m_Transform = settings.Transform;
        m_TintColor = settings.TintColor;
        m_Size = settings.Size;
        m_FlipMode = settings.FlipMode;
        m_UVScale = settings.UVScale;
    }

    void Sprite::SetVertexUV(const Array<Vector2, 4>& uv)
    {
        m_VertexUV = uv;
        SetFlip(m_FlipMode);
        SetUVScale(m_UVScale);
    }

    void Sprite::ReCalculateVertexPositions(const Vector2& textureSize)
    {
        static Vector2 s_VertexMag = Vector2::One / 2;
        Vector2 pos = s_VertexMag;

        if (std::abs(textureSize.x - textureSize.y) > 0.0001f)
            pos = textureSize.Normalized() / 2;

        pos.x *= m_Size.x;
        pos.y *= m_Size.y;

        m_VertexPositions[0] = { -pos.x, -pos.y, 0 };
        m_VertexPositions[1] = {  pos.x, -pos.y, 0 };
        m_VertexPositions[2] = {  pos.x,  pos.y, 0 };
        m_VertexPositions[3] = { -pos.x,  pos.y, 0 };
    }

    void Sprite::ApplyTransformToVertexPositions()
    {
        for (Vector3& vertexPosition : m_VertexPositions)
            vertexPosition = m_Transform * Vector4(vertexPosition, 1.);
    }

    void Sprite::SetFlip(Flip flip)
    {
        Array<Vector2, 4> uv = m_VertexUV;

        switch (flip)
        {
        case Flip::None:
            m_VertexUV = uv;
            return;
        case Flip::X:
            m_VertexUV[0] = uv[1];
            m_VertexUV[1] = uv[0];
            m_VertexUV[2] = uv[3];
            m_VertexUV[3] = uv[2];
            return;
        case Flip::Y:
            m_VertexUV[0] = uv[2];
            m_VertexUV[1] = uv[3];
            m_VertexUV[2] = uv[0];
            m_VertexUV[3] = uv[1];
            return;
        case Flip::Both:
            m_VertexUV[0] = uv[3];
            m_VertexUV[1] = uv[2];
            m_VertexUV[2] = uv[1];
            m_VertexUV[3] = uv[0];
        }

        m_FlipMode = flip;
    }

    void Sprite::SetUVScale(const Vector2& scale)
    {
        for (Vector2& uv : m_VertexUV)
        {
            uv.x *= scale.x;
            uv.y *= scale.y;
        }
    }

    void Sprite::SetSize(const Vector2& size)
    {
        m_Size = size;
        if (m_Texture)
            ReCalculateVertexPositions(m_SubTexture ? m_SubTexture->GetSize() : m_Texture->GetSize());
    }

}