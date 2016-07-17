#include <AssetManager/AssetManager.hpp>
#if defined ANDROID
    #include <Utils/Utility.hpp>
#endif

namespace ant{
    AssetManager::AssetManager()
    : textures()
    , images()
    , fonts(){}
    bool AssetManager::loadAssets(const std::string& filename){
        JsonBox::Value v;
        #if defined ANDROID
            v.loadFromString(std::string(android::readAssetsFile(filename).data()));
        #else
            v.loadFromFile(filename);
        #endif
        if(!v["textures"].isNull()){
            for(auto t:v["textures"].getArray()){
                addTexture(t["id"].getString(),t["filepath"].getString());
            }
        }
        if(!v["images"].isNull()){
            for(auto i:v["images"].getArray()){
                addImage(i["id"].getString(),i["filepath"].getString());
            }
        }
        if(!v["fonts"].isNull()){
            for(auto f:v["fonts"].getArray()){
                addFont(f["id"].getString(),f["filepath"].getString());
            }
        }
        if(!v["sounds"].isNull()){
            for(auto s:v["sounds"].getArray()){
                addSound(s["id"].getString(),s["filepath"].getString());
            }
        }
        if(!v["songs"].isNull()){
            for(auto s:v["songs"].getArray()){
                addSound(s["id"].getString(),s["filepath"].getString());
            }
        }
        return true;
    }
    void AssetManager::addTexture(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Texture> texture(std::make_unique<sf::Texture>());
        if(!texture->loadFromFile(filename)){
            throw std::runtime_error("Failed to load texture " + filename);
        }
        textures.insert(std::make_pair(id,std::move(texture)));
    }
    sf::Texture& AssetManager::getTexture(const std::string& id){
        return *(textures.at(id));
    }
    bool AssetManager::hasTexture(const std::string& id) const{
        auto found = textures.find(id);
        return (found != textures.end());
    }
    void AssetManager::removeTexture(const std::string& id){
        textures.erase(id);
    }
    void AssetManager::addImage(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Image> image(std::make_unique<sf::Image>());
        if(!image->loadFromFile(filename)){
            throw std::runtime_error("Failed to load image " + filename);
        }
        images.insert(std::make_pair(id,std::move(image)));
    }
    void AssetManager::addImage(const std::string& id, std::unique_ptr<sf::Image>&& img){
        images.insert(std::make_pair(id,std::move(img)));
    }
    sf::Image& AssetManager::getImage(const std::string& id){
        return *(images.at(id));
    }
    bool AssetManager::hasImage(const std::string& id) const{
        auto found = images.find(id);
        return (found != images.end());
    }
    void AssetManager::removeImage(const std::string& id){
        images.erase(id);
    }
    void AssetManager::addFont(const std::string& id,const std::string& filename){
        std::unique_ptr<sf::Font> font(std::make_unique<sf::Font>());
        if(!font->loadFromFile(filename)){
            throw std::runtime_error("Failed to load Font " + filename);
        }
        fonts.insert(std::make_pair(id,std::move(font)));
    }
    sf::Font& AssetManager::getFont(const std::string& id){
        return *(fonts.at(id));
    }
    bool AssetManager::hasFont(const std::string& id) const{
        auto found = fonts.find(id);
        return (found != fonts.end());
    }
    void AssetManager::removeFont(const std::string& id){
        fonts.erase(id);
    }
    void AssetManager::addSound(const std::string& id, const std::string& filename){
        auto sound = std::make_unique<sf::SoundBuffer>();
        if(!sound->loadFromFile(filename)){
            throw std::runtime_error("Failed to load Sound " + filename);
        }
        sounds.insert(std::make_pair(id,std::move(sound)));
    }
    void AssetManager::addSound(const std::string& id, std::unique_ptr<sf::SoundBuffer>&& sound){
        sounds.insert(std::make_pair(id,std::move(sound)));
    }
    sf::SoundBuffer& AssetManager::getSound(const std::string& id){
        return *(sounds.at(id));
    }
    bool AssetManager::hasSound(const std::string& id) const{
        auto found = sounds.find(id);
        return (found != sounds.end());
    }
    void AssetManager::removeSound(const std::string& id){
        sounds.erase(id);
    }
    void AssetManager::addSong(const std::string& id, const std::string& filename){
        auto song = std::make_unique<sf::Music>();
        if(!song->openFromFile(filename)){
            throw std::runtime_error("Failed to load Sound " + filename);
        }
        songs.insert(std::make_pair(id,std::move(song)));
    }
    void AssetManager::addSong(const std::string& id, std::unique_ptr<sf::Music>&& song){
        songs.insert(std::make_pair(id,std::move(song)));
    }
    sf::Music& AssetManager::getSong(const std::string& id){
        return *(songs.at(id));
    }
    bool AssetManager::hasSong(const std::string& id) const{
        auto found = songs.find(id);
        return (found != songs.end());
    }
    void AssetManager::removeSong(const std::string id){
        songs.erase(id);
    }
    bool AssetManager::clear(){
        images.clear();
        textures.clear();
        fonts.clear();
        sounds.clear();
        songs.clear();
        return true;
    }
}
