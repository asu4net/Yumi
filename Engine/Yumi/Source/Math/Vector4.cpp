#include "Vector4.h"

namespace Yumi
{
    Vector4::Vector4()
        : x(0)
        , y(0)
        , z(0)
        , w(0)
    {}

    Vector4::Vector4(float x, float y, float z, float w)
        : x(x)
        , y(y)
        , z(z)
        , w(w)
    {}

    Vector4::Vector4(const Vector3& other, float w)
        : x(other.x)
        , y(other.y)
        , z(z)
        , w(w)
    {}

    Vector4 Vector4::operator+(const Vector4& other) const
    {
        return { x + other.x, y + other.y, z + other.z, w + other.w };
    }

    void Vector4::operator+=(const Vector4& other)
    {
        *this = *this + other;
    }

    Vector4 Vector4::operator-(const Vector4& other) const
    {
        return { x - other.x, y - other.y, z - other.z, w - other.w };
    }

    void Vector4::operator-=(const Vector4& other)
    {
        *this = *this - other;
    }

    Vector4 Vector4::operator*(float num) const
    {
        return { x * num, y * num, z * num, w * num };
    }

    void Vector4::operator*=(float num)
    {
        *this = *this * num;
    }

    Vector4 Vector4::operator/(float num) const
    {
        return { x / num, y / num, z / num, w / num };
    }

    void Vector4::operator/=(float num)
    {
        *this = *this / num;
    }

    bool Vector4::operator<=(const Vector4& other)
    {
        return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
    }

    Vector4 Vector4::Abs() const
    {
        return { std::abs(x), std::abs(y), std::abs(z), std::abs(w) };
    }

    float Vector4::Magnitude() const
    {
        return std::sqrt(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2) + std::powf(w, 2));
    }

    Vector4 Vector4::Normalized() const
    {
        float mag = Magnitude();
        return { x / mag, y / mag, z / mag, w / mag };
    }

    void Vector4::Normalize()
    {
        *this = this->Normalized();
    }

    String Vector4::ToString() const
    {
        return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w);
    }

    float Vector4::Distance(const Vector4& a, const Vector4& b)
    {
        return std::sqrtf(std::powf(a.x - b.x, 2) + std::powf(a.y - b.y, 2) + std::powf(a.z - b.z, 2) + std::powf(a.w - b.w, 2));
    }
}