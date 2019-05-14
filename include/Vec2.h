#ifndef VEC_2
#define VEC_2

template<typename T>
class Vec2 final
{
    public:
        Vec2(T _x, T _y) : x{_x}, y{_y} {};
        T x;
        T y;

};

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

template<typename T>
std::ostream& operator<< (std::ostream& os, const Vec2<T> vec2)
{
    os << vec2.x << " " << vec2.y << " " << std::endl;
    return os;
}
#endif