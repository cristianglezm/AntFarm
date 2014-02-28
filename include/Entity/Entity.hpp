#ifndef ENTITY_H
#define ENTITY_H
#include "../Components/Component.hpp"
#include <string>
#include <map>
namespace ant{
    class Entity{
        private:
            std::string name;
            long int mask;
            std::map<long,Component> Components;
        public:
            Entity();
            Entity(std::string name);
            Entity(std::string name,std::map<long,Component> Components);
            void addComponent(Component component);
            inline Component getComponent(long mask){ return Components.at(mask); }
            void removeComponent(long mask);
            inline const std::string getName(){ return name; }
            void setName(std::string name);
            void setComponents(std::map<long,Component> Components);
            inline std::map<long,Component> getComponents(){ return Components; }
            inline long int const getMask(){ return mask; }
            bool operator==(const Entity& e) const;
            ~Entity();
    };
}
#endif // ENTITY_H
