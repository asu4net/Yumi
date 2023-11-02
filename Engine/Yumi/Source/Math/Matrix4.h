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
        void SetXRotation(float x);
        void SetYRotation(float y);
        void SetZRotation(float z);
        void SetRotation(const Vector3& rotation);
        void SetScale(const Vector3& scale);

        Matrix4 operator*(const Matrix4& other);
        Vector4 operator*(const Vector4& other) const;
        void operator*=(const Matrix4& other);
    };
}