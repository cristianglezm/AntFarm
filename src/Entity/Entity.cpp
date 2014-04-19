#include <Entity/Entity.hpp>
namespace ant{
        Entity::Entity(){
            this->name = "";
            this->mask = 0;
        }
        Entity::Entity(std::string name){
            this->name = name;
            this->mask = 0;
        }
        Entity::Entity(std::string name,map components){
            this->name = name;
            this->mask = 0;
            this->Components = std::move(components);
            for(auto& c: Components){
                this->mask |= c.second->getId();
            }
        }
        void Entity::addComponent(std::unique_ptr<baseComponent> component){
            auto id = component->getId();
            this->mask |= id;
            this->Components.insert(std::make_pair(id,std::move(component)));
        }
        void Entity::removeComponent(long int mask){
            this->mask &= ~mask;
            this->Components.erase(mask);
        }
        void Entity::setName(std::string name){
            this->name = name;
        }
        void Entity::setComponents(map Components){
            this->Components = std::move(Components);
            this->mask = 0;
            for(auto& c: Components){
                this->mask |= c.second->getId();
            }
        }
        bool Entity::operator==(const Entity& e) const{
            return (e.Components == Components && e.mask == mask && e.name == name);
        }
        bool Entity::operator==(const std::string& name) const{
            return (this->name == name);
        }
        Entity::~Entity(){

        }
}
