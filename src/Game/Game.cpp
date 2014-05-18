#include <Game/Game.hpp>

namespace ant{
    float Game::getFPS(const sf::Time& time) {
                return (1000000.0f / time.asMicroseconds());
    }
    Game::Game()
    :gameEventDispatcher(new GameEventDispatcher())
    ,level(new Level(Config::ASSETS_GAME_JSON,Config::screenSize,gameEventDispatcher))
    ,win(sf::VideoMode(Config::screenSize.width,Config::screenSize.height),"AntFarm", sf::Style::Close)
    ,running(true)
    ,currentLevel(0){
        eventQueue = level->getEventQueue();
        assets = level->getAssetManager();
        //win.setFramerateLimit(60);
        //win.setVerticalSyncEnabled(true);
        totalLevels = level->size();
        self.reset(this);
        isPause = false;
        gameEventDispatcher->LevelComplete.addObserver(self);
        fps.setFont(assets->getFont("Outwrite"));
        fps.setCharacterSize(25);
        fps.setPosition(Config::screenSize.width-55,Config::screenSize.height-50);
        version.setFont(assets->getFont("Outwrite"));
        version.setCharacterSize(25);
        version.setPosition(Config::screenSize.width-Config::screenSize.width+5,Config::screenSize.height-50);
        version.setString(Config::VERSION);
        GameSpeed = 1;
        loadGUIConf(Config::GUI_FILE);
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
            timePoint1 = clock.restart();
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
                            for(int i=0;i<buttons.size();++i){
                                if(buttons[i]->contains((sf::Vector2f)sf::Mouse::getPosition(win))){
                                    eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            buttons[i]->getAction()
                                                            ))
                                         );
                                }
                            }
                        }
                        if(event.mouseButton.button == sf::Mouse::Right){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::stop
                                                            ))
                                         );
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<sf::Vector2i>(EventType::SELECT_ENTITY,
                                                            sf::Mouse::getPosition(win)))
                                         );
                        }
                        break;
                    case sf::Event::KeyReleased:
                        if(event.key.code == sf::Keyboard::Escape){
                            running = false;
                        }
                        if(event.key.code == sf::Keyboard::S){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::stairs
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::D){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::downhill
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::U){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::uphill
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
                        if(event.key.code == sf::Keyboard::T){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::tunnel
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::W){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::wall
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
                        if(event.key.code == sf::Keyboard::C){
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<constructorSystem::command>(EventType::CHANGE_COMMAND,
                                                            Constructions::climb
                                                            ))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::LShift){
                            ++GameSpeed;
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<sf::Time>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)))
                                         );
                        }
                        if(event.key.code == sf::Keyboard::LControl){
                            --GameSpeed;
                            eventQueue->push(std::shared_ptr<baseEvent>(
                                    new Event<sf::Time>(EventType::CHANGE_OVERTIME,sf::seconds(GameSpeed)))
                                         );
                        }
                        break;
                    case sf::Event::KeyPressed:
                        break;
                    default:
                        break;
                }
            }
            win.clear();
            level->update(currentLevel,elapsedTime);
            while(!eventQueue->isEmpty()){
                gameEventDispatcher->DispatchEvent(eventQueue->pop());
            }
            level->render(currentLevel,win);
            win.draw(fps);
            win.draw(version);
            for(int i=0;i<buttons.size();++i){
                win.draw(*buttons[i]);
            }
            win.display();
            timePoint2 = clock.restart();
            elapsedTime = timePoint2 - timePoint1;
            lastFrame = elapsedTime;
        }
    }
    void Game::loadGUIConf(const std::string& filename){
        std::fstream file(filename);
        JsonBox::Value v(file);
        if(!v["GUI"]["buttons"].isNull()){
            int size = v["GUI"]["buttons"].getArray().size();
            for(int i=0;i<size;++i){
                sf::Vector2f pos(v["GUI"]["buttons"][size_t(i)]["position"]["x"].getInt(),
                                 v["GUI"]["buttons"][size_t(i)]["position"]["y"].getInt());
                sf::Vector2f bSize(v["GUI"]["buttons"][size_t(i)]["size"]["width"].getInt(),
                                   v["GUI"]["buttons"][size_t(i)]["size"]["height"].getInt());
                sf::Text t;
                t.setFont(assets->getFont("Outwrite"));
                t.setString(v["GUI"]["buttons"][size_t(i)]["text"]["string"].getString());
                t.setPosition(pos);
                t.setCharacterSize(v["GUI"]["buttons"][size_t(i)]["text"]["size"].getInt());
                sf::Sprite sprite;
                sprite.setPosition(pos);
                if(v["GUI"]["buttons"][size_t(i)]["imageID"].getString() != ""){
                    sprite.setTexture(assets->getTexture(v["GUI"]["buttons"][size_t(i)]["imageID"].getString()));
                }
                std::string actionID = v["GUI"]["buttons"][size_t(i)]["action"].getString();
                constructorSystem::command action;
                if(actionID == "climb"){
                    action = Constructions::climb;
                }else if(actionID == "dig"){
                    action = Constructions::hole;
                }else if(actionID == "tunnel"){
                    action = Constructions::tunnel;
                }else if(actionID == "stairs"){
                    action = Constructions::stairs;
                }else if(actionID == "wall"){
                    action = Constructions::wall;
                }else if(actionID == "stop"){
                    action = Constructions::stop;
                }else if(actionID == "bridge"){
                    action = Constructions::bridge;
                }else if(actionID == "downhill"){
                    action = Constructions::downhill;
                }else if(actionID == "uphill"){
                    action = Constructions::uphill;
                }
                buttons.push_back(Utils::makeUniquePtr<GUI::Button>(pos,bSize,sprite,t,action));
            }
        }
    }
    Game::~Game(){
        // liberamos recursos.
        self.reset(this);
        assets->clear();
        win.close();
    }
}
