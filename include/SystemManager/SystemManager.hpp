#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H
#include <map>
#include <memory>
#include <Systems/System.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ant{
    class SystemManager{
        private:
            std::map<std::string,std::shared_ptr<System> > systems;
        public:
            SystemManager();
            bool addSystem(std::shared_ptr<System> s);
            std::shared_ptr<System> getSystem(std::string name);
            void setSystems(std::map<std::string,std::shared_ptr<System>> systems);
            std::map<std::string,std::shared_ptr<System>> getSystems();
            void removeSystem(std::string name);
            void setEntityManager(std::shared_ptr<EntityManager> entityManager);
            void setEventQueue(std::shared_ptr<EventQueue> eventQueue);
            void update(sf::Time dt);
            void render(sf::RenderWindow& win);
            ~SystemManager();
    };
}
#endif // SYSTEM_MANAGER_H
