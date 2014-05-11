#include <Game/Game.hpp>

namespace ant{
    float Game::getFPS(const sf::Time& time) {
                return (1000000.0f / time.asMicroseconds());
    }
    Game::Game()
    :gameEventDispatcher(new GameEventDispatcher())
    ,level(new Level(Config::ASSETS_GAME_JSON,sf::FloatRect(0,0,800,600),gameEventDispatcher))
    ,win(sf::VideoMode(800,600),"AntFarm", sf::Style::Close)
    ,running(true)
    ,currentLevel(0){
        eventQueue = level->getEventQueue();
        assets = level->getAssetManager();
        totalLevels = level->size();
        self.reset(this);
        gameEventDispatcher->LevelComplete.addObserver(self);
        fps.setFont(assets->getFont("Outwrite"));
        fps.setCharacterSize(25);
        fps.setPosition(745,550);
        GameSpeed = 0;
    }
    void Game::onNotify(std::shared_ptr<baseEvent> e){
        switch(e->getType()){
            case EventType::LEVEL_COMPLETE:{
                if(currentLevel<(totalLevels-1)){
                    ++currentLevel;
                }else if(currentLevel == (totalLevels-1)){
                    //currentLevel = 0;
                }
            }
                break;
        }
    }
    void Game::run(){
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
            sf::Event event;
            while(win.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        running = false;
                        break;
                    case sf::Event::MouseButtonReleased:
                        if(event.mouseButton.button == sf::Mouse::Left){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<sf::Vector2i>(EventType::SELECT_ENTITY,
                                                            sf::Mouse::getPosition(win)))
                                         );
                        }
                        break;
                    case sf::Event::KeyReleased:
                        if(event.key.code == sf::Keyboard::S){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::stairs
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::B){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::bridge
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::H){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::hole
                                                            ))
                                         );
                        }
                        break;
                    case sf::Event::KeyPressed:
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
                            ++GameSpeed;
                        std::cout << GameSpeed << std::endl;
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<sf::Time>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed*100)))
                                         );
                        }
                        break;
                }
            }
            win.clear();
            level->update(currentLevel,lastFrame - elapsedTime);
            while(!eventQueue->isEmpty()){
                gameEventDispatcher->DispatchEvent(eventQueue->pop());
            }
            level->render(currentLevel,win);
            win.draw(fps);
            win.display();
            lastFrame = elapsedTime;
        }
    }
    Game::~Game(){
        // liberamos recursos.
        assets->clear();
        win.close();
    }
}
