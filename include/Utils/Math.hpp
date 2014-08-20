////////////////////////////////////////////////////////////////
// Copyright 2014 Cristian Glez <Cristian.glez.m@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
////////////////////////////////////////////////////////////////

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
         * @tparam tipo del Vector2
         * @param v1 sf::Vector2<T>
         * @param v2 sf::Vector2<T>
         * @return double
         */
        template<typename T>
        double dot(const sf::Vector2<T>& v1,const sf::Vector2<T>& v2){
            sf::Vector2f uv1 = normalize(v1);
            sf::Vector2f uv2 = normalize(v2);
            return (uv1.x * uv2.x) + (uv2.y * uv1.y);
        }
        /**
         * @brief Comprueba que un rectangulo esta completamente dentro de otro.
         * @param e sf::FloatRect rectangulo que tiene que estar dentro del otro.
         * @param bounds sf::FloatRect rectangulo en el cual tienen que estar dentro.
         * @return bool
         */
        bool RectContains(const sf::FloatRect& e,const sf::FloatRect& bounds);
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
