#include <Components/DestructableComponent/DestructableComponent.hpp>
namespace ant{
        DestructableComponent::DestructableComponent(long int id):Component(id){

        }
        void DestructableComponent::setParticles(sf::VertexArray particles){
            this->particles = particles;
        }
        inline const sf::VertexArray& DestructableComponent::getParticles(){
            return this->particles;
        }
}
