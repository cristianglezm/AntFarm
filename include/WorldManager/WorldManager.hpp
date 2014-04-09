#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H
#include <World/World.hpp>
#include <map>
#include <memory>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
namespace ant{
    class WorldManager{
        private:
            std::map<long int,std::unique_ptr<World>> worlds;
        public:
            typedef std::map<long int,std::unique_ptr<World>>::iterator iterator;
            WorldManager();
            void addWorld(std::unique_ptr<World> w);
            World* getWorld(long int id);
            void removeWorld(long int id);
            inline std::map<long int,std::unique_ptr<World>>& getWorlds(){ return this->worlds; }
            void setWorlds(std::map<long int,std::unique_ptr<World>> worlds);
            void update(long int id,sf::Time dt);
            void render(long int id,sf::RenderWindow& win);
            ~WorldManager();
    };
}
#endif // WORLD_MANAGER_H
