#include <Game/Game.hpp>

namespace ant{
    Game::Game()
    :gameEventDispatcher(new GameEventDispatcher())
    ,level(new Level(Config::ASSETS_GAME_JSON,sf::FloatRect(0,0,800,600),gameEventDispatcher))
    ,win(sf::VideoMode(800,600),"AntFarm", sf::Style::Close)
    ,running(true)
    ,currentLevel(0){
        eventQueue = level->getEventQueue();
        assets = level->getAssetManager();
    }
    void Game::run(){

        while(running){
            while(!eventQueue->isEmpty()){
                gameEventDispatcher->DispatchEvent(eventQueue->pop());
            }
            sf::Event event;
            while(win.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        running = false;
                        break;
                    case sf::Event::MouseButtonPressed:

                        break;
                }
            }
            win.clear();
            /// @todo cambiar por variables que interactuen con el sistema
            /// de userTransport para renderizar y actualizar diferentes sistemas segun el estado etc.
            level->update(currentLevel,sf::Time());
            level->render(currentLevel,win);
            win.display();
        }
        // liberamos recursos.
        assets->clear();
        win.close();
    }
    Game::~Game(){

    }
}
