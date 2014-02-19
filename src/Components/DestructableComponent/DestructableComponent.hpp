#ifndef DESTRUCTABLE_COMPONENT_H
#define DESTRUCTABLE_COMPONENT_H
#include "../Component.hpp"
#include <SFML/Graphics.hpp>
class DestructableComponent : public Component{
    private:
        sf::VertexArray particles;
    public:
        DestructableComponent(long int id);
        void setParticles(sf::VertexArray particles);
        inline const sf::VertexArray& getParticles();

};

#endif // DESTRUCTABLE_COMPONENT_H
