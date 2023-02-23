#include <Utils/Utility.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/FileInputStream.hpp>

namespace ant{
    namespace Utils{
        void centerOrigin(sf::Sprite& sprite){
            sf::FloatRect bounds = sprite.getLocalBounds();
            sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        }
        void centerOrigin(sf::Text& text){
            sf::FloatRect bounds = text.getLocalBounds();
            text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        }
        sf::Vector2f calcScale(const sf::Sprite& spr, const sf::FloatRect& bounds) noexcept{
            auto lBounds = spr.getLocalBounds();
            return {bounds.width / lBounds.width, bounds.height / lBounds.height};
        }
        sf::Vector2f calcScale(const sf::Text& txt, const sf::FloatRect& bounds) noexcept{
            auto lBounds = txt.getLocalBounds();
            return {bounds.width / lBounds.width, bounds.height / lBounds.height};
        }
        void log(const std::string& tag, const std::string& info){
#if defined ANDROID
           __android_log_write(ANDROID_LOG_INFO, tag.c_str(), info.c_str());
#else
           std::cout << tag << " - " << info << std::endl;
#endif
        }
    }
}

#if defined ANDROID
    namespace android{
        std::vector<char> readAssetsFile(std::string filename){
            sf::FileInputStream fis;
            if(!fis.open(filename)){
                throw std::runtime_error("Could not open file: " + filename);
            }
            std::vector<char> data;
            data.reserve(fis.getSize());
            int readed = 0;
            int count = 0;
            constexpr std::size_t bufferSize = 2048ull;
            std::vector<char> buffer(bufferSize, '\0');
            do{
                readed = fis.read(buffer.data(), bufferSize);
                if(readed){
                    count += readed;
                    std::copy_n(std::begin(buffer), readed, std::back_inserter(data));
                }
                fis.seek(count);
            }while(readed != 0 && readed != -1);
            return data;
        }
    }
#endif
