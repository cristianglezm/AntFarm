#include <iostream>
#include <SFML/Graphics.hpp>
#include <Utils/Quadtree.hpp>
#include <Utils/String.hpp>
#include <EntityManager/EntityManager.hpp>
#include <memory>
#include <Components/ComponentMask.hpp>

float getFPS(const sf::Time& time) {
     return (1000000.0f / time.asMicroseconds());
}

int main(){
    std::cout << "Iniciando...." << std::endl;
    // Create the main window
    ant::Utils::Quadtree qtree(sf::FloatRect(0,0,800,600));
    ant::EntityManager em;
    std::cout << "Insertando Entidades..." << std::endl;
    for(int i=0;i<100;++i){
        std::unique_ptr<ant::Entity> e1(new ant::Entity("Test" + ant::Utils::toString(i)));
        std::unique_ptr<ant::baseComponent> c1(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_TRANSFORM,sf::FloatRect(-i,i,20,20)));
        e1->addComponent(std::move(c1));
        em.addEntity(std::move(e1));
    }
    std::cout << "Agregadas al Entity Manager" << std::endl;
    for(auto& entity:em.getEntities()){
        qtree.insert(entity.get());
    }
    sf::RenderWindow app(sf::VideoMode(800, 600), "QuadTree Draw Demo");
	// Start the game loop
    while (app.isOpen()){
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        app.close();
                        break;
                }
        }
    /// Hover Mouse to destruct
        // Clear screen
        app.clear();
        // Draw the sprite
        qtree.render(app);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

