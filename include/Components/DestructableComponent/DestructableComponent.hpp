#ifndef DESTRUCTABLE_COMPONENT_H
#define DESTRUCTABLE_COMPONENT_H
#include <Components/Component.hpp>
#include <SFML/Graphics/VertexArray.hpp>
namespace ant{
    class DestructableComponent : public Component{
        private:
            sf::VertexArray particles;
        public:
            DestructableComponent(long int id);
            void setParticles(sf::VertexArray particles);
            inline const sf::VertexArray& getParticles();
    };
}
#endif // DESTRUCTABLE_COMPONENT_H
