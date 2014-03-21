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
    ant::Utils::Quadtree qtree(sf::FloatRect(3,3,795,595));
    ant::EntityManager em;
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
                    case sf::Event::MouseButtonPressed:
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                            std::unique_ptr<ant::Entity> e1(new ant::Entity("Test"));
                            int x = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).x;
                            int y = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).y;
                            std::unique_ptr<ant::baseComponent> c1(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_TRANSFORM,sf::FloatRect(x,y,20,20)));
                            e1->addComponent(std::move(c1));
                            em.addEntity(std::move(e1));
                            std::unique_ptr<ant::Entity> e2(new ant::Entity("Test"));
                            int x1 = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).x-5;
                            int y1 = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).y+5;
                            std::unique_ptr<ant::baseComponent> c2(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_TRANSFORM,sf::FloatRect(x1,y1,20,20)));
                            e2->addComponent(std::move(c2));
                            em.addEntity(std::move(e2));
                        }
                        break;
                }
        }
        qtree.clear();
    for(auto& entity:em.getEntities()){
        qtree.insert(entity.get());
    }
        // Clear screen
        app.clear();
        // Draw the sprite
        sf::VertexArray points(sf::Points,em.getEntities().size());
        for(auto& e: em.getEntities()){
            auto& properties = e->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::FloatRect>();
            sf::FloatRect eBounds = std::get<0>(properties);
            sf::Vertex p(sf::Vector2f(eBounds.left,eBounds.top),sf::Color::Green);
            points.append(p);
            app.draw(points);
            std::get<0>(properties) = sf::FloatRect(eBounds.left,eBounds.top+0.01,eBounds.width,eBounds.height);
        }
        qtree.render(app);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}

