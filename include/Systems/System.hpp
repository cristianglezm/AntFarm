#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/System/Time.hpp>
#include <string>
#include <memory>
#include <EventQueue/EventQueue.hpp>
#include <EntityManager/EntityManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
namespace ant{
    /**
     * @brief Clase base para los sistemas.
     * @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class System{
        protected:
            long int RequiredComponents;
            std::shared_ptr<EventQueue> eventQueue;
            std::shared_ptr<EntityManager> em;
            std::string name;
        public:
            System();
            System(long int req);
            System(long int req,std::shared_ptr<EntityManager> em,std::shared_ptr<EventQueue> eventQueue);
            void setRequiredComponents(long int req);
            inline long int getRequiredComponts(){ return RequiredComponents; }
            void setEventQueue(std::shared_ptr<EventQueue> eq);
            inline std::shared_ptr<EventQueue> getEventQueue(){ return eventQueue; }
            void setName(std::string name);
            inline std::string getName() const { return this->name; }
            void setEntityManager(std::shared_ptr<EntityManager> em);
            inline std::shared_ptr<EntityManager> getEntityManager(){ return this->em; }
            virtual void render(sf::RenderWindow& win) = 0;
            virtual void update(sf::Time dt) = 0;
            virtual ~System();
    };
}
#endif // SYSTEM_H
