#ifndef VEC_3
#define VEC_3

#include <iostream>

template<typename T>
class Vec3 final
{
    public:
        Vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};
        T x;
        T y;
        T z;

};

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;

template<typename T>
std::ostream& operator<< (std::ostream& os, const Vec3<T> vec3)
{
    os << vec3.x << " " << vec3.y << " " << vec3.z << std::endl;
    return os;
}
#endif