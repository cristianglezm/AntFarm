#ifndef UTILS_MATH_H
#define UTILS_MATH_H
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
namespace ant{
    namespace Utils{
        /**
         * @brief Definicion de PI
         */
        constexpr double PI = 3.14159265358979;
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
         * @fn toDegrees
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
         * @fn rotateRect
         * @brief Segun el angulo rotara el rectangulo
         * @todo !!! -Falta implementar esta funcion.
         *
         * @param rect sf::FloatRect
         * @param angle float
         * @return sf::FloatRect rectangulo rotado.
         */
        sf::FloatRect rotateRect(const sf::FloatRect& rect,const float& angle);
        /**
         * @fn getAngle
         * @brief Obtiene el angulo del vector2
         * @tparam tipo del Vector2
         * @param v sf::Vector2<T>
         * @return T
         */
        template<typename T>
        T getAngle(const sf::Vector2<T>& v){
            return atan2(-v.x,v.y);
        }
        /**
         * @fn normalize
         * @brief Normaliza un Vector
         * @param v sf::Vector2f
         * @return sf::Vector2f
         */
        sf::Vector2f normalize(const sf::Vector2f& v);
        /**
         * @fn dot
         * @brief Obtiene el dot product del vector
         *
         * behind -1
         * front 1
         * right or left 0
         *
         * @tparam tipo del Vector2
         * @param v sf::Vector2<T>
         * @return T
         */
        template<typename T>
        int dot(const sf::Vector2<T>& v1,const sf::Vector2<T>& v2){
            sf::Vector2f uv1 = normalize(v1);
            sf::Vector2f uv2 = normalize(v2);
            double r = (uv1.x * uv2.x) + (uv2.y * uv1.y);
            if(r<0){
                return -1;
            }else if(r>0){
                return 1;
            }else{
                return 0;
            }
        }
        /**
         * @fn getDirection
         * @brief Calcula el angulo en radianes respecto a otra posicion.
         * @param currentPosition sf::Vector2f
         * @param wantedPosition sf::Vector2f
         * @return float radians
         */
         float getDirection(const sf::Vector2f& currentPosition,const sf::Vector2f& wantedPosition);
    }
}
#endif // UTILS_MATH_H
