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
        : x(0)
        , y(0)
    {}

    Vector2::Vector2(float x, float y)
        : x(x)
        , y(y)
    {}

    Vector2::Vector2(const Vector3& other)
        : x(other.x)
        , y(other.y)
    {}

    bool Vector2::operator==(const Vector2& other)
    {
        return x == other.x && y == other.y;
    }

    bool Vector2::operator!=(const Vector2& other)
    {
        return x != other.x || y != other.y;
    }

    Vector2 Vector2::operator+(const Vector2& other) const
    {
        return { x + other.x, y + other.y };
    }

    Vector2 Vector2::operator-(const Vector2& other) const
    {
        return { x - other.x, y - other.y };
    }

    Vector2 Vector2::operator*(float _float) const
    {
        return { x * _float, y * _float };
    }

    Vector2 Vector2::operator/(float _float) const
    {
        return { x / _float, y / _float };
    }

    Vector2 Vector2::Abs() const
    {
        return { std::abs(x), std::abs(y) };
    }

    float Vector2::Magnitude() const
    {
        return std::sqrt(std::powf(x, 2) + std::powf(y, 2));
    }

    Vector2 Vector2::Normalized() const
    {
        float mag = Magnitude();
        return { x / mag, y / mag };
    }

    void Vector2::Normalize()
    {
        *this = this->Normalized();
    }

    String Vector2::ToString() const
    {
        return std::to_string(x) + ", " + std::to_string(y);
    }

    float Vector2::Dot(const Vector2& a, const Vector2& b)
    {
        return a.x * b.x + a.y * b.y;
    }

    float Vector2::Distance(const Vector2& a, const Vector2& b)
    {
        return std::sqrtf(std::powf(a.x - b.x, 2) + std::powf(a.y - b.y, 2));
    }

    float Vector2::Angle(const Vector2& a, const Vector2& b)
    {
        float cosAngle = Dot(a, b) / (a.Magnitude() * b.Magnitude());
        return std::acosf(cosAngle);
    }
}