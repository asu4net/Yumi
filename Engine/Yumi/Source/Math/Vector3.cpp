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
        : X(0)
        , Y(0)
        , Z(0)
    {}

    Vector3::Vector3(float x, float y, float z)
        : X(x)
        , Y(y)
        , Z(z)
    {}

    Vector3::Vector3(const Vector2& other, float z)
        : X(other.X)
        , Y(other.Y)
        , Z(z)
    {}

    Vector3& Vector3::operator+=(const Vector3& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    bool Vector3::operator<=(const Vector3& other)
    {
        return X <= other.X && Y <= other.Y && Z <= other.Z;
    }

    Vector3& Vector3::operator-=(const Vector3& other)
    {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3 Vector3::operator+(const Vector3& other) const
    {
        return { X + other.X, Y + other.Y, Z + other.Z };
    }

    Vector3 Vector3::operator-(const Vector3& other) const
    {
        return { X - other.X, Y - other.Y, Z - other.Z };
    }

    Vector3 Vector3::operator*(float num) const
    {
        return { X * num, Y * num, Z * num };
    }

    Vector3& Vector3::operator*=(float num)
    {
        X *= num;
        Y *= num;
        Z *= num;
        return *this;
    }

    Vector3& Vector3::operator/=(float num)
    {
        X /= num;
        Y /= num;
        Z /= num;
        return *this;
    }

    Vector3 Vector3::operator/(float num) const
    {
        return { X / num, Y / num, Z / num };
    }

    /*Vector3 Vector3::LookAt(const glm::quat& rot, const Vector3& axis)
    {
        const glm::mat4 matRot = glm::toMat4(rot);
        const glm::vec4 dir = glm::vec4(axis.ToGlm(), 1);
        return { matRot * dir };
    }*/

    Vector3 Vector3::Abs() const
    {
        return { std::abs(X), std::abs(Y), std::abs(Z) };
    }

    float Vector3::Magnitude() const
    {
        return std::sqrt(std::powf(X, 2) + std::powf(Y, 2) + std::powf(Z, 2));
    }

    Vector3 Vector3::Normalized() const
    {
        float mag = Magnitude();
        return { X / mag, Y / mag, Z / mag };
    }

    void Vector3::Normalize()
    {
        *this = this->Normalized();
    }

    String Vector3::ToString() const
    {
        return std::to_string(X) + ", " + std::to_string(Y) + ", " + std::to_string(Z);
    }

    float Vector3::Dot(const Vector3& a, const Vector3& b)
    {
        return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
    }

    float Vector3::Distance(const Vector3& a, const Vector3& b)
    {
        return std::sqrtf(std::powf(a.X - b.X, 2) + std::powf(a.Y - b.Y, 2) + std::powf(a.Z - b.Z, 2));
    }
}