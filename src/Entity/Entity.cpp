#include <Entity/Entity.hpp>

namespace ant{
        Entity::Entity()
        : name("")
        , mask(0)
        , states(0){}
        Entity::Entity(const std::string& name)
        : name(name)
        , mask(0)
        , states(0){}
        Entity::Entity(const std::string& name,map&& components)
        : name(name)
        , mask(0)
        , states(0){
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
        void Entity::removeComponent(const ComponentsMask::Mask& id){
            if(hasComponent(id)){
                this->mask &= ~id;
                this->Components.erase(id);
            }
        }
        void Entity::addState(const States::Mask& state){
            states |= state;
        }
        void Entity::removeState(const States::Mask& state){
            if(is(state)){
                states &= ~state;
            }
        }
        void Entity::setName(std::string name){
            this->name = name;
        }
        void Entity::setComponents(map&& Components){
            this->Components = std::move(Components);
            for(auto& c: Components){
                this->mask |= c.second->getId();
            }
        }
        void Entity::clear(){
            mask = 0;
            Components.clear();
        }
        bool Entity::operator==(const Entity& e) const noexcept{
            return (e.Components == Components && e.mask == mask && e.name == name && states == e.states);
        }
        bool Entity::operator!=(const Entity& e) const noexcept{
            return (e.Components!=Components || e.mask != mask || e.name != name || states != e.states);
        }
        bool Entity::operator==(const std::string& name) const noexcept{
            return (this->name == name);
        }
}
