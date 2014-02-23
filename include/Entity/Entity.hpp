#ifndef ENTITY_H
#define ENTITY_H
#include "../Components/Component.hpp"
#include <iostream>
#include <map>
class Entity{
    private:
        std::string name;
        long int id;
        std::map<long,Component> Components;
    public:
        Entity();
        Entity(std::string name,std::map<long,Component>);
        void addComponent(Component component);
        inline Component getComponent(long id){ return Components.at(id); }
};
#endif // ENTITY_H
