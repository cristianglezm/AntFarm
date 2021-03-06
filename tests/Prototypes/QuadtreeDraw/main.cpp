#include <iostream>
#include <SFML/Graphics.hpp>
#include <Utils/Quadtree.hpp>
#include <Utils/String.hpp>
#include <EntityManager/EntityManager.hpp>
#include <memory>
#include <ComponentFactory/ComponentFactory.hpp>
#include <Components/ComponentMask.hpp>

float getFPS(const sf::Time& time) {
    return (1000000.0f / time.asMicroseconds());
}

int main(){
    std::cout << "Iniciando...." << std::endl;
    // Create the main window
    ant::Utils::Quadtree qtree(sf::FloatRect(0,0,800,600));
    ant::EntityManager em;
    sf::RenderWindow app(sf::VideoMode(800,600), "QuadTree Draw Demo");
    sf::FloatRect worldBounds(0,0,800,600);
    ant::ComponentFactory cf;
	// Start the game loop
	sf::Time elapsedTime;
	sf::Time lastFrame;
	sf::Clock clock;
	sf::Text fps;
	sf::Text numberOfEntities;
	sf::Font Outwrite;
	if(!Outwrite.loadFromFile("../../../data/fonts/Outwrite.ttf")){
        return EXIT_FAILURE;
	}
	numberOfEntities.setFont(Outwrite);
	numberOfEntities.setCharacterSize(25);
	numberOfEntities.setPosition(10,10);
	fps.setFont(Outwrite);
	fps.setCharacterSize(25);
    fps.setPosition(745,550);
    bool running=true;
    float Speed = 0.1;
    while(running){
            elapsedTime = clock.restart();
        int FPS = getFPS(elapsedTime);

        fps.setString(ant::Utils::toString(FPS));
        if(FPS < 5){
            fps.setColor(sf::Color::Red);
        }else if(FPS > 50){
            fps.setColor(sf::Color::Green);
        }else if(FPS < 40){
            fps.setColor(sf::Color::Yellow);
        }
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        running = false;
                        break;
                    case sf::Event::MouseButtonPressed:
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                            em.getEntities().clear();
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                            running = false;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                            ++Speed;
                        }
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
                            --Speed;
                        }
                        break;
                    case sf::Event::Resized:

                        break;
                }
        }
        qtree.clear();
    for(auto& entity:em.getEntities()){
        qtree.insert(entity.get());
    }
    int emSize = em.getEntities().size();
    if(emSize<500){
        numberOfEntities.setColor(sf::Color::Green);
    }else if(emSize> 1500){
        numberOfEntities.setColor(sf::Color::Red);
    }else if(emSize>1000){
        numberOfEntities.setColor(sf::Color::Yellow);
    }
    numberOfEntities.setString(ant::Utils::toString(emSize));
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            std::unique_ptr<ant::Entity> e1(new ant::Entity("Test"));
            int x = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).x;
            int y = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).y;
            e1->addComponent(cf.createBounds(sf::FloatRect(x,y,5,5)));
            em.addEntity(std::move(e1));
    }
        // Clear screen
        app.clear();
        // Draw the sprite
        sf::VertexArray points(sf::Quads,em.getEntities().size()*4);
        ant::EntityManager::iterator e = em.getEntities().begin();
        while(e!=em.getEntities().end()){
            auto& properties = (*e)->getComponent(ComponentsMask::COMPONENT_BOUNDS)->getProperties<sf::FloatRect>();
            sf::FloatRect eBounds = std::get<0>(properties);
            points.append(sf::Vertex(sf::Vector2f(eBounds.left,eBounds.top),sf::Color::Red));
            points.append(sf::Vertex(sf::Vector2f(eBounds.left+eBounds.width,eBounds.top),sf::Color::Yellow));
            points.append(sf::Vertex(sf::Vector2f(eBounds.left+eBounds.width,eBounds.top+eBounds.height),sf::Color::Red));
            points.append(sf::Vertex(sf::Vector2f(eBounds.left,eBounds.top+eBounds.height),sf::Color::Yellow));
            if(!worldBounds.contains(eBounds.left,eBounds.top)){
                em.removeEntity(e++);
            }else{
                std::get<0>(properties) = sf::FloatRect(eBounds.left,eBounds.top+Speed,eBounds.width,eBounds.height);
            }
            app.draw(points);
            ++e;
        }
        qtree.render(app);
        // Update the window
        app.draw(fps);
        app.draw(numberOfEntities);
        app.display();
    }
    app.close();
    return EXIT_SUCCESS;
}

