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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <string>
#include <sstream>
namespace ant{
    namespace Utils{
        /**
         * @brief Convierte el Tipo a string
         * @tparam T  tipo a convertir a string.
         * @param s T tipo a convertir a string.
         * @return std::string
         */
        template<typename T>
        inline std::string toString(T s){
            std::ostringstream oss;
            oss << s;
            return oss.str();
        }
    }
}
#endif // UTILS_H
