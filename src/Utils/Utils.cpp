#include <Utils/Utils.hpp>
namespace ant{
    namespace Utils{
        std::string toString(int s){
            std::ostringstream oss;
            oss << s;
            return oss.str();
        }
    }
}
