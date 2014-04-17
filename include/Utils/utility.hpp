#ifndef ANT_UTILITY_H
#define ANT_UTILITY_H
#include <memory>
namespace ant{
    namespace Utils{
        /**
         * @brief Utilidad para crear un puntero unico.
         * @return std::unique_ptr<T<Args>>
         */
        template<typename T, typename... Args>
        std::unique_ptr<T> makeUniquePtr(Args&&... args) {
            return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
        }
        /**
         * @brief Utilidad para crear un puntero Compartido.
         * @return std::shared_ptr<T<Args>>
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> makeSharedPtr(Args&&... args) {
            return std::shared_ptr<T>(new T(args...));
        }
    }
}
#endif // ANT_UTILITY_H
