#include <Entity/Entity.hpp>
#include <Components/SpriteComponent/SpriteComponent.hpp>
#include <SFML/Graphics.hpp>
int main(){

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "AntFarm",sf::Style::Close);

    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    app.close();
                    break;
            }
        }
        // Clear screen
        app.clear(sf::Color::Red);

        app.display();
    }

    return EXIT_SUCCESS;
}
