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
        sf::Vector2f normalize(const sf::Vector2f& v){
            float length{std::sqrt((v.x * v.x) + (v.y*v.y))};
            sf::Vector2f v1;
            if(length > 1 ){
                v1.x = v.x / length;
                v1.y = v.y / length;
            }
            return v1;
        }

        float getDirection(const sf::Vector2f& currentPosition,const sf::Vector2f& wantedPosition){
            sf::Vector2f result(wantedPosition.x - currentPosition.x,wantedPosition.y - currentPosition.y);
            result = normalize(result);
            return std::atan2(-result.x, result.y);
        }

    }
}
