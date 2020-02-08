#pragma once
#include <cmath>

class Vec3
{
private:
    float x, y, z;

public:
    Vec3() = default;

    Vec3(float x, float y, float z);

    inline Vec3 operator-(const Vec3& other)
    {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }

    inline float operator*(const Vec3& other)
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 normalise();
    
    inline float getX() 
    {
        return x;
    }

    inline float getY()
    {
        return y;
    }

    inline float getZ()
    {
        return z;
    }
};

