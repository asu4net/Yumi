#pragma once

namespace Yumi
{
    struct Vector3;
    struct Vector2
    {
        float X, Y;

        static const Vector2 zero;
        static const Vector2 one;
        static const Vector2 right;
        static const Vector2 left;
        static const Vector2 up;
        static const Vector2 down;

        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector3& other);
        bool operator==(const Vector2& other);
        bool operator!=(const Vector2& other);
        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(float num) const;
        Vector2 operator/(float num) const;
        Vector2 Abs() const;
        float Magnitude() const;
        Vector2 Normalized() const;
        void Normalize();
        String ToString() const;

        static float Dot(const Vector2& a, const Vector2& b);
        static float Distance(const Vector2& a, const Vector2& b);
        static float Angle(const Vector2& a, const Vector2& b);
    };
}
