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
