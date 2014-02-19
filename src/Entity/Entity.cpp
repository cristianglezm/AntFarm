#include "Entity.hpp"

        Entity::Entity(){

        }
        Entity::Entity(std::string name,std::map<long,Component> components){
            this->name = name;
            this->Components = components;
            for(auto& c: Components){
                this->id |= c.second.getId();
            }
        }
        void Entity::addComponent(Component component){
            this->id |= component.getId();
            this->Components.insert(std::pair<long,Component>(component.getId(),component));
        }
        inline const Component Entity::getComponent(long id){
            return Components.at(id);
        }
