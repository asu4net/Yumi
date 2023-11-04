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

    Yumi::Vector3 Matrix4::GetTranslation() const
    {
        return { m[3][0], m[3][1], m[3][2] };
    }
    
    Matrix4 Matrix4::GetTransposed() const
    {
        Matrix4 transposed;
        transposed.m[0][0] = m[0][0];
        transposed.m[0][1] = m[1][0];
        transposed.m[0][2] = m[2][0];
        transposed.m[0][3] = m[3][0];
        transposed.m[1][0] = m[0][1];
        transposed.m[1][1] = m[1][1];
        transposed.m[1][2] = m[2][1];
        transposed.m[1][3] = m[3][1];
        transposed.m[2][0] = m[0][2];
        transposed.m[2][1] = m[1][2];
        transposed.m[2][2] = m[2][2];
        transposed.m[2][3] = m[3][2];
        transposed.m[3][0] = m[0][3];
        transposed.m[3][1] = m[1][3];
        transposed.m[3][2] = m[2][3];
        transposed.m[3][3] = m[3][3];
        return transposed;
    }

    void Matrix4::SetTransposed()
    {
        *this = GetTransposed();
    }

    Matrix4 Matrix4::GetInverse() const
    {
        Matrix4 inverse;
        
        float det = this->GetDeterminant();

        if (0.0f == det) {
            YLOG_WARN("Matrix has no determinant. Can not invert\n");
            return *this;
        }

        float invDet = 1.0f / det;

        inverse.n[0] = invDet * (n[9] * n[14] * n[7] - n[13] * n[10] * n[7] +
            n[13] * n[6] * n[11] - n[5] * n[14] * n[11] -
            n[9] * n[6] * n[15] + n[5] * n[10] * n[15]);
        inverse.n[1] = invDet * (n[13] * n[10] * n[3] - n[9] * n[14] * n[3] -
            n[13] * n[2] * n[11] + n[1] * n[14] * n[11] +
            n[9] * n[2] * n[15] - n[1] * n[10] * n[15]);
        inverse.n[2] = invDet * (n[5] * n[14] * n[3] - n[13] * n[6] * n[3] +
            n[13] * n[2] * n[7] - n[1] * n[14] * n[7] -
            n[5] * n[2] * n[15] + n[1] * n[6] * n[15]);
        inverse.n[3] = invDet * (n[9] * n[6] * n[3] - n[5] * n[10] * n[3] -
            n[9] * n[2] * n[7] + n[1] * n[10] * n[7] +
            n[5] * n[2] * n[11] - n[1] * n[6] * n[11]);
        inverse.n[4] = invDet * (n[12] * n[10] * n[7] - n[8] * n[14] * n[7] -
            n[12] * n[6] * n[11] + n[4] * n[14] * n[11] +
            n[8] * n[6] * n[15] - n[4] * n[10] * n[15]);
        inverse.n[5] = invDet * (n[8] * n[14] * n[3] - n[12] * n[10] * n[3] +
            n[12] * n[2] * n[11] - n[0] * n[14] * n[11] -
            n[8] * n[2] * n[15] + n[0] * n[10] * n[15]);
        inverse.n[6] = invDet * (n[12] * n[6] * n[3] - n[4] * n[14] * n[3] -
            n[12] * n[2] * n[7] + n[0] * n[14] * n[7] +
            n[4] * n[2] * n[15] - n[0] * n[6] * n[15]);
        inverse.n[7] = invDet * (n[4] * n[10] * n[3] - n[8] * n[6] * n[3] +
            n[8] * n[2] * n[7] - n[0] * n[10] * n[7] -
            n[4] * n[2] * n[11] + n[0] * n[6] * n[11]);
        inverse.n[8] = invDet * (n[8] * n[13] * n[7] - n[12] * n[9] * n[7] +
            n[12] * n[5] * n[11] - n[4] * n[13] * n[11] -
            n[8] * n[5] * n[15] + n[4] * n[9] * n[15]);
        inverse.n[9] = invDet * (n[12] * n[9] * n[3] - n[8] * n[13] * n[3] -
            n[12] * n[1] * n[11] + n[0] * n[13] * n[11] +
            n[8] * n[1] * n[15] - n[0] * n[9] * n[15]);
        inverse.n[10] = invDet * (n[4] * n[13] * n[3] - n[12] * n[5] * n[3] +
            n[12] * n[1] * n[7] - n[0] * n[13] * n[7] -
            n[4] * n[1] * n[15] + n[0] * n[5] * n[15]);
        inverse.n[11] = invDet * (n[8] * n[5] * n[3] - n[4] * n[9] * n[3] -
            n[8] * n[1] * n[7] + n[0] * n[9] * n[7] +
            n[4] * n[1] * n[11] - n[0] * n[5] * n[11]);
        inverse.n[12] = invDet * (n[12] * n[9] * n[6] - n[8] * n[13] * n[6] -
            n[12] * n[5] * n[10] + n[4] * n[13] * n[10] +
            n[8] * n[5] * n[14] - n[4] * n[9] * n[14]);
        inverse.n[13] = invDet * (n[8] * n[13] * n[2] - n[12] * n[9] * n[2] +
            n[12] * n[1] * n[10] - n[0] * n[13] * n[10] -
            n[8] * n[1] * n[14] + n[0] * n[9] * n[14]);
        inverse.n[14] = invDet * (n[12] * n[5] * n[2] - n[4] * n[13] * n[2] -
            n[12] * n[1] * n[6] + n[0] * n[13] * n[6] +
            n[4] * n[1] * n[14] - n[0] * n[5] * n[14]);
        inverse.n[15] = invDet * (n[4] * n[9] * n[2] - n[8] * n[5] * n[2] +
                n[8] * n[1] * n[6] - n[0] * n[9] * n[6] -
                n[4] * n[1] * n[10] + n[0] * n[5] * n[10]);

        return inverse;
    }

    float Matrix4::GetDeterminant() const
    {
        return n[12] * n[9] * n[6] * n[3] -
            n[8] * n[13] * n[6] * n[3] -
            n[12] * n[5] * n[10] * n[3] +
            n[4] * n[13] * n[10] * n[3] +
            n[8] * n[5] * n[14] * n[3] -
            n[4] * n[9] * n[14] * n[3] -
            n[12] * n[9] * n[2] * n[7] +
            n[8] * n[13] * n[2] * n[7] +
            n[12] * n[1] * n[10] * n[7] -
            n[0] * n[13] * n[10] * n[7] -
            n[8] * n[1] * n[14] * n[7] +
            n[0] * n[9] * n[14] * n[7] +
            n[12] * n[5] * n[2] * n[11] -
            n[4] * n[13] * n[2] * n[11] -
            n[12] * n[1] * n[6] * n[11] +
            n[0] * n[13] * n[6] * n[11] +
            n[4] * n[1] * n[14] * n[11] -
            n[0] * n[5] * n[14] * n[11] -
            n[8] * n[5] * n[2] * n[15] +
            n[4] * n[9] * n[2] * n[15] +
            n[8] * n[1] * n[6] * n[15] -
            n[0] * n[9] * n[6] * n[15] -
            n[4] * n[1] * n[10] * n[15] +
            n[0] * n[5] * n[10] * n[15];
    }

    void Matrix4::SetInverse()
    {
        *this = this->GetInverse();
    }

    Matrix4 Matrix4::operator*(const Matrix4& other) const
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

    Vector4 Matrix4::operator*(const Vector4& other) const
    {
        Matrix4 otherMat = Matrix4::Translate(Matrix4(), other);
        Matrix4 resultMat = otherMat * (*this);
        return resultMat.GetTranslation();
    }

    bool Matrix4::operator==(const Matrix4& other) const
    {
        bool isEqual = true;

        for (uint32_t i = 0; i < 4; i++)
        {
            for (uint32_t j = 0; j < 4; j++)
            {
                if (m[i][j] == other.m[i][j])
                {
                    continue;
                }
                isEqual = false;
                break;
            }
        }

        return isEqual;
    }

    bool Matrix4::operator!=(const Matrix4& other) const
    {
        return !(*this == other);
    }

    Matrix4 Matrix4::CreateTransform(const Vector3& position, const Vector3& rotation /*= Vector3::Zero*/, const Vector3& scale /*= Vector3::One*/)
    {
        Matrix4 transform = Matrix4::Translate(Matrix4(), position)
            * Matrix4::Rotate(Matrix4(), rotation)
            * Matrix4::Scale(Matrix4(), scale);
        return transform;
    }

    Matrix4 Matrix4::Translate(const Matrix4& matrix, const Vector3& translation)
    {
        Matrix4 translateMatrix;
        translateMatrix.m[3][0] = translation.x;
        translateMatrix.m[3][1] = translation.y;
        translateMatrix.m[3][2] = translation.z;
        return matrix * translateMatrix;
    }

    Matrix4 Matrix4::Rotate(const Matrix4& matrix, const Vector3& rotation)
    {
        Matrix4 rotateMatrix;

        const float x = rotation.x;
        const float y = rotation.y;
        const float z = rotation.z;

        rotateMatrix.m[1][1] = cos(x) + cos(z);
        rotateMatrix.m[1][2] = sin(x);
        rotateMatrix.m[2][1] = -sin(x);
        rotateMatrix.m[2][2] = cos(x) + cos(y);
        rotateMatrix.m[0][0] = cos(y) + cos(z);
        rotateMatrix.m[0][2] = sin(y);
        rotateMatrix.m[2][0] = -sin(y);
        rotateMatrix.m[0][1] = sin(z);
        rotateMatrix.m[1][0] = -sin(z);

        return matrix * rotateMatrix;
    }

    Matrix4 Matrix4::Scale(const Matrix4& matrix, const Vector3& scale)
    {
        Matrix4 scaleMatrix;

        scaleMatrix.m[0][0] = scale.x;
        scaleMatrix.m[1][1] = scale.y;
        scaleMatrix.m[2][2] = scale.z;

        return matrix * scaleMatrix;
    }

    Matrix4 Matrix4::OrthoProjection(float left, float right, float bottom, float top, float near, float far)
    {
        Matrix4 mat;
        mat.m[0][0] = 2 / (right - left);
        mat.m[1][1] = 2 / (top - bottom);
        mat.m[2][2] = -1;
        mat.m[3][0] = -(right + left) / (right - left);
        mat.m[3][1] = -(top + bottom) / (top - bottom);
        return mat;
    }

    Matrix4 Matrix4::ViewProjection(const Vector3& position, const Vector3& rotation)
    {
        Vector3 tweakedPosition = position;
        tweakedPosition.z *= -1;
        Matrix4 viewMatrix = Matrix4::CreateTransform(position, rotation);
        return viewMatrix.GetInverse();
    }
}