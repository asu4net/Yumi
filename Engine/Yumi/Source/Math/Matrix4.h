#pragma once

namespace Yumi
{
    struct Vector4;

    class Matrix4
    {
    public:
        float m[4][4]; //i = row, j = column
        
        Matrix4();

        void SetIdentity();
        void SetTranslation(const Vector3& translation);
        Vector3 GetTranslation() const;

        void SetXRotation(float x);
        void SetYRotation(float y);
        void SetZRotation(float z);
        void SetRotation(const Vector3& rotation);
        void SetScale(const Vector3& scale);

        Matrix4 operator*(const Matrix4& other);
        Vector4 operator*(const Vector4& other) const;
        void operator*=(const Matrix4& other);
        bool operator==(const Matrix4& other) const;
        bool operator!=(const Matrix4& other) const;

        static Matrix4 GetOrthoProjection(float left, float right, float bottom, float top, float near, float far);
    };
}