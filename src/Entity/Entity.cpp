#include <Entity/Entity.hpp>

        Entity::Entity(){
            this->name = "";
            this->mask = 0;
        }
        Entity::Entity(std::string name,std::map<long,Component> components){
            this->name = name;
            this->mask = 0;
            this->Components = components;
            for(auto& c: Components){
                this->mask |= c.second.getId();
            }
        }
        void Entity::addComponent(Component component){
            this->mask |= component.getId();
            this->Components.insert(std::pair<long,Component>(component.getId(),component));
        }
        void Entity::removeComponent(long mask){
            this->mask &= ~mask;
            this->Components.erase(mask);
        }
        void Entity::setName(std::string name){
            this->name = name;
        }
        void Entity::setComponents(std::map<long,Component> Components){
            this->Components = Components;
            for(auto& c: Components){
                this->mask |= c.second.getId();
            }
        }
