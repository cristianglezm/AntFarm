#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/System/Time.hpp>
#include <string>
#include <EventQueue/EventQueue.hpp>
namespace ant{
    class System{
        private:
            long int RequiredComponents;
            EventQueue eventQueue;
            std::string name;
        public:
            System();
            void setRequiredComponents(long int req);
            inline long int getRequiredComponts(){ return RequiredComponents; }
            void setEventQueue(EventQueue& eq);
            inline EventQueue getEventQueue(){ return eventQueue; }
            void setName(std::string name);
            inline std::string getName(){ return this->name; }
            virtual void render(){};
            virtual void update(sf::Time dt){};
            ~System();
    };
}
#endif // SYSTEM_H
