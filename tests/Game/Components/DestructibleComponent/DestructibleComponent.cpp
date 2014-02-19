#include "../Component.cpp"
#ifndef _SFML_
#include <SFML/Graphics.hpp>
#endif // _SFML_
class Destructible : public Component{
    private:
        sf::VertexArray liveParticles;
        sf::VertexArray staticParticles;
    public:
        Destructible(long int id):Component(id){

        }
        void setLiveParticles(sf::VertexArray liveParticles){
            this->liveParticles = liveParticles;
        }
        inline const sf::VertexArray getLiveParticles(){
            return this->liveParticles;
        }
        void setStaticParticles(sf::VertexArray staticParticles){
            this->staticParticles = staticParticles;
        }
        inline const sf::VertexArray getStaticParticles(){
            return this->staticParticles;
        }

};
