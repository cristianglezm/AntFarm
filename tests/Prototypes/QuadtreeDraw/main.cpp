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
    sf::RenderWindow app(sf::VideoMode(800, 600), "QuadTree Draw Demo");
    sf::FloatRect worldBounds(0,0,800,600);
	// Start the game loop
	sf::Time elapsedTime;
	sf::Time lastFrame;
	sf::Clock clock;
	sf::Text fps;
	sf::Font font;
	if(!font.loadFromFile("../../../data/fonts/OLDFAX.ttf")){
        return EXIT_FAILURE;
	}
	fps.setFont(font);
	fps.setCharacterSize(25);
    fps.setPosition(745,550);
    bool running=true;
    while(running){
        int FPS = getFPS(clock.restart());
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
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                                for(int i=0;i<2;++i){
                                    std::unique_ptr<ant::Entity> e1(new ant::Entity("Test"));
                                    int x = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).x;
                                    int y = app.mapCoordsToPixel((sf::Vector2f)sf::Mouse::getPosition(app)).y;
                                    std::unique_ptr<ant::baseComponent> c1(new ant::Component<sf::FloatRect>(ComponentsMask::COMPONENT_TRANSFORM,sf::FloatRect(x+i*2,y,1,1)));
                                    e1->addComponent(std::move(c1));
                                    em.addEntity(std::move(e1));
                                }
                        }
                        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                            em.getEntities().clear();
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
        std::list<std::unique_ptr<ant::Entity>>::iterator e = em.getEntities().begin();
        while(e!=em.getEntities().end()){
            auto& properties = (*e)->getComponent(ComponentsMask::COMPONENT_TRANSFORM)->getProperties<sf::FloatRect>();
            sf::FloatRect eBounds = std::get<0>(properties);
            sf::Vertex p(sf::Vector2f(eBounds.left,eBounds.top),sf::Color::Green);
            points.append(p);
            app.draw(points);
            std::get<0>(properties) = sf::FloatRect(eBounds.left,eBounds.top+0.05,eBounds.width,eBounds.height);
            if(!worldBounds.contains(eBounds.left,eBounds.top)){
                em.getEntities().erase(e++);
            }
            ++e;
        }
        qtree.render(app);
        // Update the window
        app.draw(fps);
        app.display();
    }
    app.close();
    return EXIT_SUCCESS;
}

