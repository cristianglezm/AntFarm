#include <Utils/Math.hpp>

namespace ant{
    namespace Utils{
        sf::FloatRect rotateRect(const sf::FloatRect& rect,const float& angle){
            sf::Vector2f UL;
            UL.x = rect.left;
            UL.y = rect.top;
            UL.x = UL.x + (rect.width / 2) * std::sin(toRadians(angle)) + (rect.width / 2) * std::cos(toRadians(angle));
            UL.y = UL.y - (rect.height / 2) * std::cos(toRadians(angle)) + (rect.height / 2) * std::sin(toRadians(angle));
            sf::FloatRect nRect;
            nRect.left = UL.x;
            nRect.top = UL.y;
            nRect.width = rect.width;
            nRect.height = rect.height;
            return nRect;
        }
    }
}
