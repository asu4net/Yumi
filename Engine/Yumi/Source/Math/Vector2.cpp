#include "Vector2.h"

namespace Yumi
{
    const Vector2 Vector2::zero = { 0, 0 };
    const Vector2 Vector2::one = { 1, 1 };
    const Vector2 Vector2::right = { 1, 0 };
    const Vector2 Vector2::left = { -1, 0 };
    const Vector2 Vector2::up = { 0, 1 };
    const Vector2 Vector2::down = { 0, -1 };

    Vector2::Vector2()
        : X(0)
        , Y(0)
    {}

    Vector2::Vector2(float x, float y)
        : X(x)
        , Y(y)
    {}

    Vector2::Vector2(const Vector3& other)
        : X(other.X)
        , Y(other.Y)
    {}

    bool Vector2::operator==(const Vector2& other)
    {
        return X == other.X && Y == other.Y;
    }

    bool Vector2::operator!=(const Vector2& other)
    {
        return X != other.X || Y != other.Y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return { X + other.X, Y + other.Y };
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return { X - other.X, Y - other.Y };
    }

    Vector2 Vector2::operator*(float _float) const
    {
        return { X * _float, Y * _float };
    }

    Vector2 Vector2::operator/(float _float) const
    {
        return { X / _float, Y / _float };
    }

    Vector2 Vector2::Abs() const
    {
        return { std::abs(X), std::abs(Y) };
    }

    float Vector2::Magnitude() const
    {
        return std::sqrt(std::powf(X, 2) + std::powf(Y, 2));
    }

    Vector2 Vector2::Normalized() const
    {
        float mag = Magnitude();
        return { X / mag, Y / mag };
    }

    void Vector2::Normalize()
    {
        *this = this->Normalized();
    }

    float Vector2::Dot(const Vector2& a, const Vector2& b)
    {
        return a.X * b.X + a.Y * b.Y;
    }

    float Vector2::Distance(const Vector2& a, const Vector2& b)
    {
        return std::sqrtf(std::powf(a.X - b.X, 2) + std::powf(a.Y - b.Y, 2));
    }

    float Vector2::Angle(const Vector2& a, const Vector2& b)
    {
        float cosAngle = Dot(a, b) / (a.Magnitude() * b.Magnitude());
        return std::acosf(cosAngle);
    }
}