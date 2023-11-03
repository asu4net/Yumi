#pragma once

namespace Yumi
{
    struct Vector4;

    class Matrix4
    {
    public:
        union
        {
            float m[4][4]; //i = row, j = column
            float n[16];
        };
        
        Matrix4();

        void SetIdentity();
        Vector3 GetTranslation() const;
        Matrix4 GetTransposed() const;
        void SetTransposed();
        Matrix4 GetInverse() const;
        float GetDeterminant() const;
        void SetInverse();

        Matrix4 operator*(const Matrix4& other) const;
        Vector4 operator*(const Vector4& other) const;
        void operator*=(const Matrix4& other);
        bool operator==(const Matrix4& other) const;
        bool operator!=(const Matrix4& other) const;

        static Matrix4 CreateTransform(const Vector3& position, const Vector3& rotation = Vector3::Zero, const Vector3& scale = Vector3::One);
        static Matrix4 Translate(const Matrix4& matrix, const Vector3& translation);
        static Matrix4 Rotate(const Matrix4& matrix, const Vector3& rotation);
        static Matrix4 Scale(const Matrix4& matrix, const Vector3& scale);

        static Matrix4 OrthoProjection(float left, float right, float bottom, float top, float near, float far);
        static Matrix4 ViewProjection(const Vector3& position, const Vector3& rotation);
    };
}