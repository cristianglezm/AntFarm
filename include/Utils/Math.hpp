#ifndef UTILS_MATH_H
#define UTILS_MATH_H
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
namespace ant{
    namespace Utils{
        /**
         * @brief Definicion de PI
         */
        const double PI = 3.14159265358979;
        /**
         * @brief Convertira el valor introducido a radianes.
         * @tparam T tipo a convertir a radianes
         * @param degrees T (float,double,char,int,long) etc
         * @return T
         */
        template<typename T>
        inline T toRadians(T degrees){
           return (T)(degrees * ( PI / 180));
        }
        /**
         * @brief Convertira el valor introducido a grados.
         * @tparam T tipo a convertir a degrees
         * @param radians T (float,double,char,int,long) etc
         * @return T
         */
        template<typename T>
        inline T toDegrees(T radians){
           return (T)(radians * (180 / PI));
        }
        /**
         * @brief Segun el angulo rotara el rectangulo
         * @todo !!! -Falta implementar esta funcion.
         *
         * @param rect sf::FloatRect
         * @param angle float
         * @return sf::FloatRect rectangulo rotado.
         */
        sf::FloatRect rotateRect(const sf::FloatRect& rect,const float& angle);
    }
}
#endif // UTILS_MATH_H
