#include "Vec3.h"

Vec3 Vec3::normalise()
{
    if (x == 0 && y == 0 && z == 0)
        return *this;

    float length = std::sqrt(x * x + y * y + z * z);

    x /= length;
    y /= length;
    z /= length;

    return *this;
}

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}