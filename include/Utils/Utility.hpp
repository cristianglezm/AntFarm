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

#ifndef ANT_UTILITY_H
#define ANT_UTILITY_H
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
namespace ant{
    namespace Utils{
        /**
         * @brief Utilidad para crear un puntero unico.
         * @tparam T clase para crear el puntero
         * @tparam args Args argumentos
         * @return std::unique_ptr<T<Args>>
         */
        template<typename T, typename... Args>
        std::unique_ptr<T> makeUniquePtr(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
        /**
         * @brief Utilidad para crear un puntero Compartido.
         * @tparam T clase para crear el puntero
         * @tparam args Args argumentos
         * @return std::shared_ptr<T<Args>>
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> makeSharedPtr(Args&&... args) {
            return std::shared_ptr<T>(new T(args...));
        }
        /**
         * @brief Centra el texto
         * @param text sf::Text & referencia al texto.
         */
        void centerOrigin(sf::Text& text);
        /**
         * @brief Centra el sprite
         * @param sprite sf::Sprite & referencia al sprite.
         */
        void centerOrigin(sf::Sprite& sprite);
    }
}
#endif // ANT_UTILITY_H
