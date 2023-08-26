#include "Matrix4.h"

namespace Yumi
{
    Matrix4::Matrix4()
    {
        SetIdentity();
    }

    void Matrix4::SetIdentity()
    {
        memset(m, 0, sizeof(float) * 16);
        m[0][0] = 1;
        m[1][1] = 1;
        m[2][2] = 1;
        m[3][3] = 1;
    }

    void Matrix4::SetTranslation(const Vector3& translation)
    {
        m[3][0] = translation.x;
        m[3][1] = translation.y;
        m[3][2] = translation.z;
    }

    void Matrix4::SetXRotation(float x)
    {
        m[1][1] =  cos(x);
        m[1][2] =  sin(x);
        m[2][1] = -sin(x);
        m[2][2] =  cos(x);
    }

    void Matrix4::SetYRotation(float y)
    {
        m[0][0] =  cos(y);
        m[0][2] = -sin(y);
        m[2][0] =  sin(y);
        m[2][2] =  cos(y);
    }

    void Matrix4::SetZRotation(float z)
    {
        m[0][0] =  cos(z);
        m[0][1] =  sin(z);
        m[1][0] = -sin(z);
        m[1][1] =  cos(z);
    }

    void Matrix4::SetRotation(const Vector3& rotation)
    {
        SetXRotation(rotation.x);
        SetYRotation(rotation.y);
        SetZRotation(rotation.z);
    }

    void Matrix4::SetScale(const Vector3& scale)
    {
        m[0][0] = scale.x;
        m[1][1] = scale.y;
        m[2][2] = scale.z;
    }
    
    Matrix4 Matrix4::operator*(const Matrix4& other)
    {
        Matrix4 result;

        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                result.m[i][j] =
                    m[i][0] * other.m[0][j] +
                    m[i][1] * other.m[1][j] +
                    m[i][2] * other.m[2][j] +
                    m[i][3] * other.m[3][j];
            }
        }
        return result;
    }

    void Matrix4::operator*=(const Matrix4& other)
    {
        *this = operator*(other);
    }
}