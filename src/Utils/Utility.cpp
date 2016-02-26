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
    }
}

#if defined ANDROID
        namespace android{
            std::string readAssetsFile(std::string filename){
                sf::FileInputStream fis;
                if(!fis.open(filename)){
                    throw std::runtime_error("Could not open file: " + filename);
                }
                std::string data;
                char buffer[1024];
                while(fis.read((void*)&buffer,1024)){
                    data += std::string(buffer);
                }
                return data;
            }
            void log(std::string tag,std::string info){
                __android_log_write(ANDROID_LOG_INFO, tag.c_str(), info.c_str());
            }
        }
#endif