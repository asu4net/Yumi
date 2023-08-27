#include "Vector3.h"

namespace Yumi
{
    const Vector3 Vector3::zero = { 0, 0, 0 };
    const Vector3 Vector3::one = { 1, 1, 1 };
    const Vector3 Vector3::right = { 1, 0, 0 };
    const Vector3 Vector3::left = { -1, 0, 0 };
    const Vector3 Vector3::up = { 0, 1, 0 };
    const Vector3 Vector3::down = { 0, -1, 0 };
    const Vector3 Vector3::back = { 0, 0, -1 };
    const Vector3 Vector3::forward = { 0, 0, 1 };

    Vector3::Vector3()
        : x(0)
        , y(0)
        , z(0)
    {}

    Vector3::Vector3(float x, float y, float z)
        : x(x)
        , y(y)
        , z(z)
    {}

    Vector3::Vector3(const Vector2& other, float z)
        : x(other.x)
        , y(other.y)
        , z(z)
    {}

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return { x + other.x, y + other.y, z };
    }

    void Vector3::operator+=(const Vector3& other)
    {
        *this = *this + other;
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return { x - other.x, y - other.y, z - other.z };
    }

    void Vector3::operator-=(const Vector3& other)
    {
        *this = *this - other;
    }

    Vector3 Vector3::operator*(float num) const
    {
        return { x * num, y * num, z * num };
    }

    void Vector3::operator*=(float num)
    {
        *this = *this * num;
    }

    Vector3 Vector3::operator/(float num) const
    {
        return { x / num, y / num, z / num };
    }

    void Vector3::operator/=(float num)
    {
        *this = *this / num;
    }

    bool Vector3::operator<=(const Vector3& other)
    {
        return x <= other.x && y <= other.y && z <= other.z;
    }

    /*Vector3 Vector3::LookAt(const glm::quat& rot, const Vector3& axis)
    {
        const glm::mat4 matRot = glm::toMat4(rot);
        const glm::vec4 dir = glm::vec4(axis.ToGlm(), 1);
        return { matRot * dir };
    }*/

    Vector3 Vector3::Abs() const
    {
        return { std::abs(x), std::abs(y), std::abs(z) };
    }

    float Vector3::Magnitude() const
    {
        return std::sqrt(std::powf(x, 2) + std::powf(y, 2) + std::powf(z, 2));
    }

    Vector3 Vector3::Normalized() const
    {
        float mag = Magnitude();
        return { x / mag, y / mag, z / mag };
    }

    void Vector3::Normalize()
    {
        *this = this->Normalized();
    }

    String Vector3::ToString() const
    {
        return std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z);
    }

    float Vector3::Dot(const Vector3& a, const Vector3& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    float Vector3::Distance(const Vector3& a, const Vector3& b)
    {
        return std::sqrtf(std::powf(a.x - b.x, 2) + std::powf(a.y - b.y, 2) + std::powf(a.z - b.z, 2));
    }
}