#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H
#include <World/World.hpp>
#include <map>
#include <memory>

namespace ant{
    class WorldManager{
        private:
            std::map<std::string,std::unique_ptr<World>> worlds;
        public:
            WorldManager();
            void addWorld(std::unique_ptr<World> w);
            World* getWorld(std::string id);
            bool removeWorld(std::string id);
            inline std::map<std::string,std::unique_ptr<World>>& getWorlds(){ return this->worlds; }
            void setWorlds(std::map<std::string,std::unique_ptr<World>> worlds);
            ~WorldManager();
    };
};
#endif // WORLD_MANAGER_H
