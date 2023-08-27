#pragma once

namespace Yumi
{
    struct Vector2;

    struct Vector3
    {
        float x, y, z;

        static const Vector3 zero;
        static const Vector3 one;
        static const Vector3 right;
        static const Vector3 left;
        static const Vector3 up;
        static const Vector3 down;
        static const Vector3 forward;
        static const Vector3 back;

        Vector3();
        Vector3(float x, float y, float z);
        Vector3(const Vector2& other, float z = 0);

        Vector3 operator+(const Vector3& other) const;
        void operator+=(const Vector3& other);
        Vector3 operator-(const Vector3& other) const;
        void operator-=(const Vector3& other);
        Vector3 operator*(float num) const;
        void operator*=(float num);
        Vector3 operator/(float num) const;
        void operator/=(float num);
        bool operator<=(const Vector3& other);
        
        Vector3 Abs() const;
        float Magnitude() const;
        Vector3 Normalized() const;
        void Normalize();
        String ToString() const;

        //static Vector3 LookAt(const glm::quat& rot, const Vector3& axis);
        static float Dot(const Vector3& a, const Vector3& b);
        static float Distance(const Vector3& a, const Vector3& b);
    };
}
