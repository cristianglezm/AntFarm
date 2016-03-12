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
            std::vector<char> readAssetsFile(std::string filename){
                sf::FileInputStream fis;
                if(!fis.open(filename)){
                    throw std::runtime_error("Could not open file: " + filename);
                }
                std::vector<char> data;
                data.reserve(fis.getSize());
                int readed = 0;
                int count = 0;
                auto bufferSize = 2048;
                do{
                    std::vector<char> buffer(bufferSize,'\0');
                    readed = fis.read(buffer.data(), bufferSize);
                    count += readed;
                    for(auto& byte:buffer){
                        data.emplace_back(byte);
                    }
                    fis.seek(count);
                }while(readed != 0 && readed != -1);
                return data;
            }
            void log(std::string tag,std::string info){
                __android_log_write(ANDROID_LOG_INFO, tag.c_str(), info.c_str());
            }
        }
#endif
