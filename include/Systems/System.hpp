#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/System/Time.hpp>
#include <string>
#include <EventQueue/EventQueue.hpp>
#include <EntityManager/EntityManager.hpp>
namespace ant{
    /**
     * @brief Clase base para los sistemas.
     * @author Cristian Gonzalez Moreno <Cristian.glez.m@gmail.com>
     * @version 0.1
     */
    class System{
        protected:
            long int RequiredComponents;
            EventQueue eventQueue;
            std::shared_ptr<EntityManager> em;
            std::string name;
        public:
            System(long int req);
            System();
            void setRequiredComponents(long int req);
            inline long int getRequiredComponts(){ return RequiredComponents; }
            void setEventQueue(EventQueue& eq);
            inline EventQueue& getEventQueue(){ return eventQueue; }
            void setName(std::string name);
            inline std::string getName() const { return this->name; }
            void setEntityManager(std::shared_ptr<EntityManager> em);
            inline std::shared_ptr<EntityManager>& getEntityManager(){ return this->em; }
            virtual void render() = 0;
            virtual void update(sf::Time dt) = 0;
            virtual ~System();
    };
}
#endif // SYSTEM_H
