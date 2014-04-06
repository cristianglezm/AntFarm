#ifndef UTILS_MATH_H
#define UTILS_MATH_H
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
namespace ant{
    namespace Utils{
        const double PI = 3.14159265358979;
        template<typename T>
        inline T toRadians(T degrees){
           return (T)(degrees * ( PI / 180));
        }
        template<typename T>
        inline T toDegrees(T radians){
           return (T)(radians * (180 / PI));
        }
        sf::FloatRect rotateRect(const sf::FloatRect& rect,const float& angle);
    }
}
#endif // UTILS_MATH_H
