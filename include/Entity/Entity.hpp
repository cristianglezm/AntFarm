#ifndef ENTITY_H
#define ENTITY_H
#include <Components/Component.hpp>
#include <string>
#include <memory>
#include <map>
namespace ant{
    class Entity{
        private:
            std::string name;
            long int mask;
            std::map<long,std::unique_ptr<Component> > Components;
        public:
            Entity();
            Entity(std::string name);
            Entity(std::string name,std::map<long,std::unique_ptr<Component> > Components);
            void addComponent(std::unique_ptr<Component> component);
            inline std::unique_ptr<Component>& getComponent(long mask){ return Components.at(mask); }
            void removeComponent(long mask);
            inline const std::string getName(){ return name; }
            void setName(std::string name);
            void setComponents(std::map<long,std::unique_ptr<Component> > Components);
            inline std::map<long,std::unique_ptr<Component> >& getComponents(){ return Components; }
            inline long int const getMask(){ return mask; }
            bool operator==(const Entity& e) const;
            ~Entity();
    };
}
#endif // ENTITY_H
