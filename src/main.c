#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cmath>
#ifndef _SFML_
#include <SFML/Graphics.hpp>
#endif // _SFML_
int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "AntFarm");


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
        // Clear screen
        app.clear();

        app.display();
    }

    return EXIT_SUCCESS;
}
